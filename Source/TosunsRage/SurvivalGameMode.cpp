// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"

void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	GetWorldTimerManager().SetTimer(TosunWaitHandle, this, &ASurvivalGameMode::SpawnTosun, 10, true, 1);
	GetWorldTimerManager().SetTimer(BombTosunWaitHandle, this, &ASurvivalGameMode::SpawnBombTosun, 10, true, 1);
	GetWorldTimerManager().SetTimer(BigTosunWaitHandle, this, &ASurvivalGameMode::SpawnBigTosun, 40, true, 1);
}

void ASurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivalGameMode::SetIsGameOver(bool bIsGameOver)
{
	IsGameOver = bIsGameOver;
}

void ASurvivalGameMode::SpawnTosun()
{
	if (IsGameOver)
	{
		GetWorldTimerManager().ClearTimer(TosunWaitHandle);
		return;
	}

	// float X = FMath::RandRange(-1420.f, 380.f);
	// float Y = FMath::RandRange(-350.f, 750.f);
	FVector Location(-130, -260, 691);
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(Tosun, Location, Rotation);

	Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(Tosun, Location, Rotation);
}

void ASurvivalGameMode::SpawnBombTosun()
{
	if (IsGameOver)
	{
		GetWorldTimerManager().ClearTimer(BombTosunWaitHandle);
		return;
	}

	// float X = FMath::RandRange(-1420.f, 380.f);
	// float Y = FMath::RandRange(-350.f, 750.f);
	FVector Location(-220, -670, 691);
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(BombTosun, Location, Rotation);

	Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(BombTosun, Location, Rotation);
}

void ASurvivalGameMode::SpawnBigTosun()
{
	if (IsGameOver)
	{
		GetWorldTimerManager().ClearTimer(BigTosunWaitHandle);
		return;
	}

	// float X = FMath::RandRange(-1420.f, 380.f);
	// float Y = FMath::RandRange(-350.f, 750.f);
	FVector Location(-1240, 150, 691);
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);

	Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);
}