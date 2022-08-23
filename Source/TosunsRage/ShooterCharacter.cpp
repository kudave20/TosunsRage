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
}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();

	Health = MaxHealth;
	
	Gun = GetWorld()->SpawnActor<AGun>(GunClass);
	Gun->AttachToComponent(Arms, FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this);
}

float AShooterCharacter::GetHealth() const
{
	return Health;
}

bool AShooterCharacter::GetIsAiming() const
{
	return IsAiming;
}

AGun* AShooterCharacter::GetGun() const
{
	return Gun;
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
	Gun->PullTrigger();
}

void AShooterCharacter::Die()
{
	UE_LOG(LogTemp, Warning, TEXT("I'M DEAD!"));

	IsDead = true;
}

void AShooterCharacter::Reload()
{
	Gun->Reload();
}

void AShooterCharacter::Aim()
{
	AimTimeLineSet();
}

void AShooterCharacter::AimTimeLineSet()
{
	if (AimCurveFloat != nullptr)
	{
		FOnTimelineFloat TimeLineCallback;
		FOnTimelineEventStatic TimeLineFinishedCallback;

		TimeLineCallback.BindUFunction(this, FName("SetAimLocation"));
		TimeLineFinishedCallback.BindUFunction(this, FName("SetADSLocation"));

		AimTimeLine.AddInterpFloat(AimCurveFloat, TimeLineCallback);
		AimTimeLine.SetTimelineFinishedFunc(TimeLineFinishedCallback);

		if (IsAiming)
		{
			AimTimeLine.Reverse();

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

void AShooterCharacter::SetAimLocation(float Value)
{
	FVector NewArmLocation = FMath::Lerp<FVector, float>(FVector(1.6f, 7.8f, -23.6775f), FVector(-8, 0, -16), Value);

	Arms->SetRelativeLocation(NewArmLocation);
}
