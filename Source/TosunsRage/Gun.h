// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UENUM(BlueprintType)
enum class EGunType : uint8
{
	GLOCK26 UMETA(DisplayName = "GLOCK26"),
	MP5 UMETA(DisplayName = "MP5"),
	AK74 UMETA(DisplayName = "AK74"),
};

UCLASS()
class TOSUNSRAGE_API AGun : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AGun();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure)
	int32 GetMaxAmmo() const;

	UFUNCTION(BlueprintPure)
	int32 GetAmmo() const;

	UFUNCTION(BlueprintPure)
	EGunType GetGunType() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void PullTrigger();

	void Reload();

	void Aim();

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	class UPointLightComponent* Light;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* Flame;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BulletHole;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* GunSound;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* DrySound;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* ArmsReloadAnim;

	UPROPERTY(EditDefaultsOnly)
	UAnimMontage* GunReloadAnim;

	UPROPERTY(EditAnywhere)
	float MaxRange = 100000;

	UPROPERTY(EditAnywhere)
	float Damage = 10;

	UPROPERTY(EditDefaultsOnly)
	int32 MaxAmmo;

	UPROPERTY(VisibleAnywhere)
	int32 Ammo;

	UPROPERTY(EditDefaultsOnly)
	EGunType GunType;

	bool IsReloading;
	bool IsAiming;

	void SetNextFlame();
};
