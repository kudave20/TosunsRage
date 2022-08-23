// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.h"

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
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();

	Ammo = MaxAmmo;
}

int32 AGun::GetMaxAmmo() const
{
	return MaxAmmo;
}

int32 AGun::GetAmmo() const
{
	return Ammo;
}

EGunType AGun::GetGunType() const
{
	return GunType;
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGun::PullTrigger()
{
	if (IsReloading) return;

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
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
	FHitResult Hit;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(OwnerPawn);
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

	// Activate Muzzle Flash
	Light->SetIntensity(20000);
	Flame->SetVisibility(true);

	FTimerHandle WaitHandle;

	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			Light->SetIntensity(0);
			Flame->SetVisibility(false);
			SetNextFlame();
		}, 0.1f, false);

	// Spawn Bullet Decal
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHole, FVector(3.2f, 6.4f, 6.4f), Hit.Location, Hit.ImpactPoint.Rotation());
	Decal->FadeScreenSize = 0.00001f;
	Decal->FadeStartDelay = 180;
	Decal->FadeDuration = 5;
}

void AGun::Reload()
{
	if (Ammo == MaxAmmo) return;

	IsReloading = true;

	AShooterCharacter* OwnerCharacter = Cast<AShooterCharacter>(GetOwner());
	if (OwnerCharacter == nullptr) return;

	float ReloadTime = OwnerCharacter->PlayArmsAnimMontage(ArmsReloadAnim);
	Mesh->PlayAnimation(GunReloadAnim, false);

	FTimerHandle WaitHandle;

	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			Ammo = MaxAmmo;
			IsReloading = false;
		}, ReloadTime, false);
}

void AGun::Aim()
{
	if (IsReloading) return;

	IsAiming = true;
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

