// Fill out your copyright notice in the Description page of Project Settings.


#include "Tosun.h"
#include "ShooterCharacter.h"
#include "Kismet/GameplayStatics.h"

void ATosun::BeginPlay()
{
	Super::BeginPlay();

	RForeArm = GetMesh()->GetBodyInstance("RightForeArm");
}

void ATosun::Attack()
{
	Super::Attack();

	IsAttacking = true;
}

void ATosun::AttackStart()
{
	FTransform T = RForeArm->GetUnrealWorldTransform();

	AttackStartPosition = T.GetLocation();
}

void ATosun::AttackEnd()
{
	FTransform T = RForeArm->GetUnrealWorldTransform();

	TArray<FHitResult> OutHits;

	FVector Location = T.GetLocation();
	FQuat Rotation = T.GetRotation();
	FVector Direction = Location - AttackStartPosition;

	GetWorld()->SweepMultiByProfile(
		OutHits,
		AttackStartPosition,
		Location + Direction * 2,
		Rotation,
		FName(TEXT("Pawn")),
		FCollisionShape::MakeSphere(50));

	for (FHitResult OutHit : OutHits)
	{
		AShooterCharacter* Player = Cast<AShooterCharacter>(OutHit.GetActor());

		if (Player != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, OutHit, Direction, nullptr);
			Player->TakeDamage(Damage, DamageEvent, GetController(), this);
		}
	}
}

