// Fill out your copyright notice in the Description page of Project Settings.


#include "BigTosun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void ABigTosun::Attack()
{
	Super::Attack();

	IsAttacking = true;

	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Direction;

	FTimerHandle WaitHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SplashAttack"), Direction);

	GetWorldTimerManager().SetTimer(WaitHandle, TimerDelegate, 1.5f, false);
}

void ABigTosun::SplashAttack(FVector Direction)
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	TArray<FHitResult> Hits;

	bool bSuccess = UKismetSystemLibrary::SphereTraceMulti(GetWorld(), GetActorLocation(), GetActorLocation(), 300,
		UEngineTypes::ConvertToTraceType(ECC_Camera), true, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, Hits, true);

	if (bSuccess)
	{
		for (FHitResult Hit : Hits)
		{
			AShooterCharacter* Player = Cast<AShooterCharacter>(Hit.GetActor());

			if (Player != nullptr)
			{
				FPointDamageEvent DamageEvent(Damage, Hit, -Direction, nullptr);
				Player->TakeDamage(Damage, DamageEvent, GetController(), this);
			}
		}
	}
}