// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"
#include "Components/TimelineComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(GetCapsuleComponent());

	Arms = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Arms"));
	Arms->SetupAttachment(Camera);
	Arms->SetVisibility(false);
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
}

float AShooterCharacter::GetHealth() const
{
	return Health;
}

bool AShooterCharacter::GetIsAiming() const
{
	return IsAiming;
}

bool AShooterCharacter::GetIsReloading() const
{
	return IsReloading;
}

AGun* AShooterCharacter::GetGun() const
{
	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			return PrimaryGun;
		case EGunSlot::SECONDARY:
			return SecondaryGun;
	}

	return nullptr;
}

EGunType AShooterCharacter::GetGunType() const
{
	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			return PrimaryGunType;
		case EGunSlot::SECONDARY:
			return SecondaryGunType;
	}

	return EGunType::NONE;
}

void AShooterCharacter::SetIsReloading(bool bIsReloading)
{
	IsReloading = bIsReloading;
}

void AShooterCharacter::SetIsAiming(bool bIsAiming)
{
	IsAiming = bIsAiming;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	AimTimeLine.TickTimeline(DeltaTime);
}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight);
	PlayerInputComponent->BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Shoot"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Shoot);
	PlayerInputComponent->BindAction(TEXT("Reload"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Reload);
	PlayerInputComponent->BindAction(TEXT("Aim"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Aim);
	PlayerInputComponent->BindAction(TEXT("Drop"), EInputEvent::IE_Pressed, this, &AShooterCharacter::UnEquip);
	PlayerInputComponent->BindAction(TEXT("Switch"), EInputEvent::IE_Pressed, this, &AShooterCharacter::Switch);
	PlayerInputComponent->BindAction(TEXT("EquipPrimary"), EInputEvent::IE_Pressed, this, &AShooterCharacter::EquipPrimary);
	PlayerInputComponent->BindAction(TEXT("EquipSecondary"), EInputEvent::IE_Pressed, this, &AShooterCharacter::EquipSecondary);
}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Health -= DamageToApply;

	if (Health > 0) UGameplayStatics::PlaySound2D(GetWorld(), HurtSound);

	if (Health <= 0 && !IsDead) Die();

	return DamageToApply;
}

float AShooterCharacter::PlayArmsAnimMontage(UAnimMontage* ArmsAnimMontage)
{
	UAnimInstance* AnimInstance = Arms->GetAnimInstance();

	if (AnimInstance != nullptr)
	{
		float ReloadTime = AnimInstance->Montage_Play(ArmsAnimMontage);
		return ReloadTime;
	}
	
	return 0;
}

void AShooterCharacter::Equip(EGunSlot GunSlot, EGunType GunType, TSubclassOf<AGun> GunClass)
{
	switch (GunSlot)
	{
		case EGunSlot::PRIMARY:
			PrimaryGun = GetWorld()->SpawnActor<AGun>(GunClass);
			PrimaryGun->AttachToComponent(Arms, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			PrimaryGun->SetOwner(this);
			PrimaryGunType = GunType;

			if (SecondaryGun != nullptr) SecondaryGun->GetMesh()->SetVisibility(false);

			break;
		case EGunSlot::SECONDARY:
			SecondaryGun = GetWorld()->SpawnActor<AGun>(GunClass);
			SecondaryGun->AttachToComponent(Arms, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
			SecondaryGun->SetOwner(this);
			SecondaryGunType = GunType;

			if (PrimaryGun != nullptr) PrimaryGun->GetMesh()->SetVisibility(false);

			break;
	}

	EquippedGunSlot = GunSlot;
	Arms->SetVisibility(true);
}

void AShooterCharacter::AimTimeLineSet()
{
	if (AimCurveFloat != nullptr)
	{
		FOnTimelineFloat TimeLineCallback;

		TimeLineCallback.BindUFunction(this, FName("SetAimLocation"));

		AimTimeLine.AddInterpFloat(AimCurveFloat, TimeLineCallback);
		AimTimeLine.SetLooping(false);

		if (IsAiming)
		{
			AimTimeLine.Reverse();

			Arms->SetRelativeRotation(FRotator(0).Quaternion());

			IsAiming = false;
		}
		else
		{
			AimTimeLine.PlayFromStart();

			Arms->SetRelativeRotation(FRotator(0, -1.06f, 0).Quaternion());

			IsAiming = true;
		}
	}
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			if (PrimaryGun != nullptr) PrimaryGun->PullTrigger();
			break;
		case EGunSlot::SECONDARY:
			if (SecondaryGun != nullptr) SecondaryGun->PullTrigger();
			break;
	}
}

void AShooterCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("I'M DEAD!"));

	IsDead = true;
}

void AShooterCharacter::Reload()
{
	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			PrimaryGun->Reload();
			break;
		case EGunSlot::SECONDARY:
			SecondaryGun->Reload();
			break;
	}
}

void AShooterCharacter::Aim()
{
	AimTimeLineSet();
}

void AShooterCharacter::SetAimLocation(float Value)
{
	FVector NewArmLocation = FMath::Lerp<FVector, float>(FVector(1.6f, 7.8f, -23.6775f), FVector(-8, 0, -16), Value);
	Arms->SetRelativeLocation(NewArmLocation);

	if (EquippedGunSlot == EGunSlot::PRIMARY)
	{
		float NewCameraFOV = FMath::Lerp<float, float>(90, 60, Value);
		Camera->SetFieldOfView(NewCameraFOV);
	}
}

void AShooterCharacter::EquipPrimary()
{
	if (EquippedGunSlot == EGunSlot::PRIMARY) return;

	if (SecondaryGun != nullptr) SecondaryGun->GetMesh()->SetVisibility(false);

	if (PrimaryGun == nullptr) Arms->SetVisibility(false);
	else
	{
		Arms->SetVisibility(true);
		PrimaryGun->GetMesh()->SetVisibility(true);
	}

	EquippedGunSlot = EGunSlot::PRIMARY;
}

void AShooterCharacter::EquipSecondary()
{
	if (EquippedGunSlot == EGunSlot::SECONDARY) return;

	if (PrimaryGun != nullptr) PrimaryGun->GetMesh()->SetVisibility(false);

	if (SecondaryGun == nullptr) Arms->SetVisibility(false);
	else
	{
		Arms->SetVisibility(true);
		SecondaryGun->GetMesh()->SetVisibility(true);
	}

	EquippedGunSlot = EGunSlot::SECONDARY;
}

void AShooterCharacter::Switch()
{
	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			if (SecondaryGun == nullptr) return;

			if (PrimaryGun != nullptr) PrimaryGun->GetMesh()->SetVisibility(false);
			
			Arms->SetVisibility(true);
			SecondaryGun->GetMesh()->SetVisibility(true);
			
			EquippedGunSlot = EGunSlot::SECONDARY;
			
			break;
		case EGunSlot::SECONDARY:
			if (PrimaryGun == nullptr) return;

			if (SecondaryGun != nullptr) SecondaryGun->GetMesh()->SetVisibility(false);
			Arms->SetVisibility(true);
			PrimaryGun->GetMesh()->SetVisibility(true);

			EquippedGunSlot = EGunSlot::PRIMARY;

			break;
	}
}

void AShooterCharacter::UnEquip()
{
	if (IsReloading) return;

	switch (EquippedGunSlot)
	{
		case EGunSlot::PRIMARY:
			PrimaryGun->SetMaxAmmo(0);
			PrimaryGun->GetMesh()->SetVisibility(false);
			PrimaryGun = nullptr;
			PrimaryGunType = EGunType::NONE;
			break;
		case EGunSlot::SECONDARY:
			SecondaryGun->SetMaxAmmo(0);
			SecondaryGun->GetMesh()->SetVisibility(false);
			SecondaryGun = nullptr;
			SecondaryGunType = EGunType::NONE;
			break;
	}

	Arms->SetVisibility(false);

	IsAiming = false;
}
