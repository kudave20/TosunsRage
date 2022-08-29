// Fill out your copyright notice in the Description page of Project Settings.


#include "Fluorescent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/PointLightComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "Components/AudioComponent.h"

// Sets default values
AFluorescent::AFluorescent()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	Light = CreateDefaultSubobject<UPointLightComponent>(TEXT("Light"));
	Light->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void AFluorescent::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFluorescent::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AFluorescent::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	if (IsCrashed) return DamageToApply;

	Spark = GetWorld()->SpawnActor<AActor>(SparkClass, Light->GetComponentLocation(), FRotator(0));

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, [&]()
		{
			GetWorld()->DestroyActor(Spark);
		}, 3, false);

	Light->SetVisibility(false);
	Mesh->SetMaterial(1, PlasticSet);

	IsCrashed = true;

	return DamageToApply;
}

