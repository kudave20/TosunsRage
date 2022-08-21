// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/PointLightComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

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

void AGun::PullTrigger()
{
	UGameplayStatics::SpawnSoundAttached(GunSound, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr) return;

	AController* OwnerController = OwnerPawn->GetController();
	if (OwnerController == nullptr) return;

	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);

	FVector End = Location + Rotation.Vector() * MaxRange;
	FHitResult Hit;
	FCollisionQueryParams Params;

	Params.AddIgnoredActor(OwnerPawn);

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
		}, 0.1f, false);

	float RandomFloat = FMath::RandRange(-90.f, 90.f);
	FRotator NewRotation(90);
	NewRotation.Pitch += RandomFloat;

	Flame->SetRelativeRotation(NewRotation);

	RandomFloat = FMath::RandRange(0.2f, 0.3f);
	Flame->SetWorldScale3D(FVector(RandomFloat));

	// Spawn Bullet Decal
	UDecalComponent* Decal = UGameplayStatics::SpawnDecalAtLocation(GetWorld(), BulletHole, FVector(3.2f, 6.4f, 6.4f), Hit.Location, Hit.ImpactPoint.Rotation());
	Decal->FadeScreenSize = 0.00001f;
	Decal->FadeStartDelay = 180;
	Decal->FadeDuration = 5;
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

