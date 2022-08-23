// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class TOSUNSRAGE_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	float GetHealth() const;

	UFUNCTION(BlueprintPure)
	bool GetIsAiming() const;

	UFUNCTION(BlueprintPure)
	AGun* GetGun() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	float PlayArmsAnimMontage(UAnimMontage* ArmsAnimMontage);

private:
	UPROPERTY(VisibleAnywhere)
	class UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Arms;

	UPROPERTY(EditAnywhere)
	float RotationRate = 70;

	UPROPERTY(EditDefaultsOnly)
	float MaxHealth = 100;

	UPROPERTY(VisibleAnywhere)
	float Health;

	bool IsDead;

	bool IsAiming;

	UPROPERTY(EditAnywhere)
	USoundBase* HurtSound;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass;

	UPROPERTY()
	AGun* Gun;

	UPROPERTY(EditDefaultsOnly)
	UCurveFloat* AimCurveFloat;

	FTimeline AimTimeLine;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);

	void Shoot();
	void Die();

	void Reload();
	void Aim();

	void AimTimeLineSet();

	UFUNCTION()
	void SetAimLocation(float Value);
};
