// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.h"
#include "Camera/CameraComponent.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Root);

	Flame = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Flame"));
	Flame->SetupAttachment(Root);

	Suppressor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Suppressor"));
	Suppressor->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;

	FireRate = 60 / FireRate;
}

int32 AGun::GetMaxAmmo() const
{
	return MaxAmmo;
}

int32 AGun::GetAmmo() const
{
	return Ammo;
}

float AGun::GetFireRate() const
{
	return FireRate;
}

bool AGun::GetIsInFullAuto() const
{
	return IsInFullAuto;
}

USkeletalMeshComponent* AGun::GetMesh() const
{
	return Mesh;
}

UStaticMeshComponent* AGun::GetSuppressor() const
{
	return Suppressor;
}

TSubclassOf<APickUp> AGun::GetPickUpClass() const
{
	return PickUpClass;
}

void AGun::SetMaxAmmo(int Value)
{
	MaxAmmo = Value;
	Ammo = MaxAmmo;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	RecoilTimeLine.TickTimeline(DeltaTime);
	RecoveryTimeLine.TickTimeline(DeltaTime);
}

void AGun::PullTrigger()
{
	AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(GetOwner());
	if (OwnerCharacter == nullptr) return;

	if (OwnerCharacter->GetIsReloading()) return;

	AController* OwnerController = OwnerCharacter->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	if (Ammo == 0)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), DrySound, Location);
		return;
	}

	Ammo--;

	UGameplayStatics::SpawnSoundAttached(GunSound, Mesh, TEXT("MuzzleFlashSocket"));

	FVector End = Location + Rotation.Vector() * MaxRange;

	if (!OwnerCharacter->GetIsAiming())
	{
		FVector RandomVector(FMath::RandRange(-BulletSpread, BulletSpread), FMath::RandRange(-BulletSpread, BulletSpread), FMath::RandRange(-BulletSpread, BulletSpread));
		End += RandomVector;
	}

	FHitResult Hit;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(OwnerCharacter);
	Params.AddIgnoredActor(this);

	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);

	// Give Damage
	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		AActor* HitActor = Hit.GetActor();

		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr);
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
		}
	}

	// Spawn Bullet Decal
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHole, FVector(3.2f, 6.4f, 6.4f), Hit.Location, Hit.ImpactPoint.Rotation());
	Decal->FadeScreenSize = 0.00001f;
	Decal->FadeStartDelay = 180;
	Decal->FadeDuration = 5;

	UAnimInstance* AnimInstance = OwnerCharacter->GetArms()->GetAnimInstance();
	if (AnimInstance == nullptr) return;
	
	if (OwnerCharacter->GetIsAiming()) AnimInstance->Montage_Play(ArmsADSShootAnim);
	else AnimInstance->Montage_Play(ArmsShootAnim);

	Mesh->PlayAnimation(ShootAnim, false);

	// Activate Muzzle Flash
	Light->SetIntensity(20000);
	Flame->SetVisibility(true);

	FTimerHandle WaitHandle;

	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			Light->SetIntensity(0);
			Flame->SetVisibility(false);
			SetNextFlame();
		}, 0.05f, false);
}

void AGun::RecoilStart()
{
	APawn* Pawn = GetOwner<APawn>();
	if (Pawn == nullptr) return;

	AController* Controller = Pawn->GetController();
	if (Controller == nullptr) return;

	RecoilStartRotation = Controller->GetControlRotation();
	RecoilDeltaRotation = FRotator(0);

	if (RecoilCurveVector != nullptr)
	{
		if (!RecoilTimeLineCallback.IsBound())
		{
			RecoilTimeLineCallback.BindUFunction(this, FName("Recoil"));

			RecoilTimeLine.AddInterpVector(RecoilCurveVector, RecoilTimeLineCallback);
			RecoilTimeLine.SetLooping(false);
		}

		RecoilTimeLine.PlayFromStart();
	}
}

void AGun::RecoveryStart()
{
	DeltaRotation = FRotator(0);
	RecoveryDeltaRotation = FRotator(0);

	RecoilTimeLine.Stop();

	APawn* Pawn = GetOwner<APawn>();
	if (Pawn == nullptr) return;

	AController* Controller = Pawn->GetController();
	if (Controller == nullptr) return;

	RecoveryStartRotation = Controller->GetControlRotation();
	FRotator Rotation = RecoveryStartRotation - RecoilStartRotation;

	if (RecoilDeltaRotation.Pitch >= FMath::Abs(Rotation.Pitch)) RecoilDeltaRotation.Pitch = FMath::Abs(Rotation.Pitch);
	else RecoilDeltaRotation.Pitch = 0;

	if (RecoveryCurveFloat != nullptr)
	{
		if (!RecoveryTimeLineCallback.IsBound())
		{
			RecoveryTimeLineCallback.BindUFunction(this, FName("Recovery"));

			RecoveryTimeLine.AddInterpFloat(RecoveryCurveFloat, RecoveryTimeLineCallback);
			RecoveryTimeLine.SetLooping(false);
		}

		RecoveryTimeLine.PlayFromStart();
	}
}

void AGun::Reload()
{
	if (Ammo == MaxAmmo) return;

	AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(GetOwner());
	if (OwnerCharacter == nullptr) return;

	OwnerCharacter->SetIsReloading(true);

	if (OwnerCharacter->GetIsAiming()) OwnerCharacter->AimTimeLineSet();

	float ReloadTime = OwnerCharacter->PlayArmsAnimMontage(ArmsReloadAnim);
	Mesh->PlayAnimation(GunReloadAnim, false);

	FTimerHandle WaitHandle;

	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			Ammo = MaxAmmo;

			AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(GetOwner());
			if (OwnerCharacter == nullptr) return;

			OwnerCharacter->SetIsReloading(false);
		}, ReloadTime, false);
}

void AGun::Recoil(FVector Value)
{
	if (Ammo == 0)
	{
		AShooterCharacter* Player = GetOwner<AShooterCharacter>();
		if (Player != nullptr) Player->SetIsRecovering(true);

		RecoveryStart();
		return;
	}

	APawn* Pawn = GetOwner<APawn>();
	if (Pawn == nullptr) return;

	AController* Controller = Pawn->GetController();

	if (Controller != nullptr)
	{
		FRotator Rotation;
		Rotation.Pitch = Value.Y;
		Rotation.Yaw = Value.Z;
		Rotation.Roll = 0;

		Controller->SetControlRotation(Controller->GetControlRotation() - DeltaRotation + Rotation);

		RecoilDeltaRotation += Rotation - DeltaRotation;
		DeltaRotation = Rotation;
	}

	if (!IsInFullAuto) RecoilTimeLine.Stop();
}

void AGun::Recovery(float Value)
{
	APawn* Pawn = GetOwner<APawn>();
	if (Pawn == nullptr) return;

	AController* Controller = Pawn->GetController();
	if (Controller == nullptr) return;

	FRotator Rotation = FMath::Lerp<FRotator, float>(RecoveryStartRotation, RecoveryStartRotation - RecoilDeltaRotation, Value) - RecoveryStartRotation;

	Controller->SetControlRotation(Controller->GetControlRotation() - RecoveryDeltaRotation + Rotation);

	RecoveryDeltaRotation = Rotation;
}

void AGun::SetNextFlame()
{
	float RandomFloat = FMath::RandRange(-90.f, 90.f);
	FRotator NewRotation(90);
	NewRotation.Pitch += RandomFloat;

	Flame->SetRelativeRotation(NewRotation);

	RandomFloat = FMath::RandRange(0.2f, 0.3f);
	Flame->SetWorldScale3D(FVector(RandomFloat));
}

