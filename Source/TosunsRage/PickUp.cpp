// Fill out your copyright notice in the Description page of Project Settings.


#include "PickUp.h"
#include "Components/SphereComponent.h"
#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
APickUp::APickUp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Sphere = CreateDefaultSubobject<USphereComponent>(TEXT("Sphere"));
	Sphere->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();

	SetSphereCollision();

	Sphere->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OverlapBegin);
}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APickUp::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AShooterCharacter* Player = Cast<AShooterCharacter>(OtherActor);
	if (Player == nullptr) return;

	if (!Player->GetIsReloading())
	{
		switch (GunSlot)
		{
			case EGunSlot::PRIMARY:
				if (Player->GetPrimaryGun() == nullptr)
				{
					Player->Equip(GunSlot, GunType, GunClass);
					GetWorld()->DestroyActor(this);
				}

				break;
			case EGunSlot::SECONDARY:
				if (Player->GetSecondaryGun() == nullptr)
				{
					Player->Equip(GunSlot, GunType, GunClass);
					GetWorld()->DestroyActor(this);
				}

				break;
		}

	}
}

void APickUp::SetSphereCollision()
{
	Sphere->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	FTimerHandle WaitHandle;

	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			Sphere->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
		}, 0.6f, false);
}

