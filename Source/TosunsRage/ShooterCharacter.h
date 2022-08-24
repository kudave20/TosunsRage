// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "ShooterCharacter.generated.h"

UENUM(BlueprintType)
enum class EGunSlot : uint8
{
	PRIMARY UMETA(DisplayName = "PRIMARY"),
	SECONDARY UMETA(DisplayName = "SECONDARY"),
};

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

	bool GetIsReloading() const;

	UFUNCTION(BlueprintPure)
	AGun* GetGun() const;

	UFUNCTION(BlueprintPure)
	EGunType GetGunType() const;

	void SetIsReloading(bool bIsReloading);

	void SetIsAiming(bool bIsAiming);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

	float PlayArmsAnimMontage(UAnimMontage* ArmsAnimMontage);

	void Equip(EGunSlot GunSlot, EGunType GunType, TSubclassOf<AGun> GunClass);

	void AimTimeLineSet();

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
	bool IsReloading;

	UPROPERTY(EditAnywhere)
	USoundBase* HurtSound;

	UPROPERTY()
	AGun* PrimaryGun;

	UPROPERTY()
	AGun* SecondaryGun;

	EGunType PrimaryGunType;
	EGunType SecondaryGunType;

	EGunSlot EquippedGunSlot;

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

	UFUNCTION()
	void SetAimLocation(float Value);

	void EquipPrimary();
	void EquipSecondary();

	void Switch();

	void UnEquip();
};
