// Fill out your copyright notice in the Description page of Project Settings.


#include "BombTosun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void ABombTosun::BeginPlay()
{
	Super::BeginPlay();
}

void ABombTosun::Attack()
{
	Super::Attack();

	IsAttacking = true;

	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Direction;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(this);

	FHitResult Hit;

	bool bSuccess = UKismetSystemLibrary::SphereTraceSingle(GetWorld(), Start, End, 25,
		UEngineTypes::ConvertToTraceType(ECC_Camera), true, ActorsToIgnore,
		EDrawDebugTrace::ForDuration, Hit, true);

	if (bSuccess)
	{
		AShooterCharacter* Player = Cast<AShooterCharacter>(Hit.GetActor());

		if (Player != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, -Direction, nullptr);
			Player->TakeDamage(Damage, DamageEvent, GetController(), this);
		}
	}

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

	Die();
}