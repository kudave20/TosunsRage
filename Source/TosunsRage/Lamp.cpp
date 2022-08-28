// Fill out your copyright notice in the Description page of Project Settings.


#include "Lamp.h"
#include "Kismet/GameplayStatics.h"
#include "Components/SpotLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
ALamp::ALamp()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Light = CreateDefaultSubobject<USpotLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ALamp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ALamp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float ALamp::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	Spark = GetWorld()->SpawnActor<AActor>(SparkClass, Light->GetComponentLocation() - FVector(0, 0, 15), FRotator(0));

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			GetWorld()->DestroyActor(Spark);
		}, 3, false);

	Light->SetVisibility(false);
	Mesh->SetMaterial(1, PlasticSet);

	return DamageToApply;
}
