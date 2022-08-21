// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"
#include "TimerManager.h"
#include "AIController.h"
#include "BrainComponent.h"

// Sets default values
AEnemy::AEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth;
}

bool AEnemy::GetIsAttacking()
{
	return IsAttacking;
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AEnemy::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageToApply;

	if (Health > 0) UGameplayStatics::PlaySound2D(GetWorld(), HitSound);

	if (Health <= 0 && !IsDead) Die();

	return DamageToApply;
}

void AEnemy::Attack()
{
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
		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, -Direction, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, GetController(), this);
		}
	}
}

void AEnemy::SetIsAttacking(bool bIsAttacking)
{
	IsAttacking = bIsAttacking;
}

void AEnemy::Die()
{
	// Ragdoll
	UCapsuleComponent* CapsuleComp = GetCapsuleComponent();
	CapsuleComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	CapsuleComp->SetCollisionResponseToAllChannels(ECR_Ignore);

	GetMesh()->SetCollisionProfileName(TEXT("Ragdoll"));
	SetActorEnableCollision(true);

	GetMesh()->SetAllBodiesSimulatePhysics(true);
	GetMesh()->SetSimulatePhysics(true);
	GetMesh()->WakeAllRigidBodies();
	GetMesh()->bBlendPhysics = true;

	UCharacterMovementComponent* CharacterComp = Cast<UCharacterMovementComponent>(GetMovementComponent());
	if (CharacterComp != nullptr)
	{
		CharacterComp->StopMovementImmediately();
		CharacterComp->DisableMovement();
		CharacterComp->SetComponentTickEnabled(false);
	}

	SetLifeSpan(10.0f);

	// Play UI Sound
	UGameplayStatics::PlaySound2D(GetWorld(), KillSound);

	if (FMath::RandBool()) UGameplayStatics::PlaySound2D(GetWorld(), KillVoice);

	// Stop Behavior Tree
	AAIController* AIController = Cast<AAIController>(GetOwner());
	FString Reason;

	if (AIController != nullptr) AIController->GetBrainComponent()->StopLogic(Reason);

	IsDead = true;
}

