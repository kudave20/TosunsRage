// Fill out your copyright notice in the Description page of Project Settings.


#include "BigTosun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void ABigTosun::Attack()
{
	Super::Attack();

	IsAttacking = true;
}

void ABigTosun::SplashAttack()
{
	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> Hits;

	bool bSuccess = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 300,
		UEngineTypes::ConvertToTraceType(ECC_Camera), true, ActorsToIgnore,
		EDrawDebugTrace::None, Hits, true);

	if (bSuccess)
	{
		for (FHitResult Hit : Hits)
		{
			AShooterCharacter* Player = Cast<AShooterCharacter>(Hit.GetActor());

			if (Player != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, Direction, nullptr);
				Player->TakeDamage(Damage, DamageEvent, GetController(), this);
			}
		}
	}
}