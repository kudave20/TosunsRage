// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"

void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::SpawnTosun, 7, true, 1);
}

void ASurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivalGameMode::SpawnTosun()
{
	if (IsGameOver) return;

	// float X = FMath::RandRange(-1420.f, 380.f);
	// float Y = FMath::RandRange(-350.f, 750.f);
	FVector Location(-130, -260, 691);
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(Tosun, Location, Rotation);

	Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(Tosun, Location, Rotation);
}