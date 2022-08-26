// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Enemy.generated.h"

UCLASS()
class TOSUNSRAGE_API AEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

protected:
	bool IsAttacking;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
	void SphereTrace(FVector Direction, FVector Start, FVector End);

	void Die();

public:
	UFUNCTION(BlueprintPure)
	bool GetIsAttacking();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	virtual void Attack();

	virtual void SetIsAttacking(bool bIsAttacking);

private:
	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 20;

	UPROPERTY(VisibleAnywhere)
	float Health;

	UPROPERTY(EditAnywhere)
	USoundBase* HitSound;

	UPROPERTY(EditAnywhere)
	USoundBase* KillSound;

	UPROPERTY(EditAnywhere)
	USoundBase* KillVoice;

	bool IsDead;
};
