// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void ASurvivalGameMode::BeginPlay()
{
	Super::BeginPlay();

	PlayStarting();

	GetWorldTimerManager().SetTimer(TosunWaitHandle, this, &ASurvivalGameMode::SpawnTosun, 10, true, 3);
	GetWorldTimerManager().SetTimer(BombTosunWaitHandle, this, &ASurvivalGameMode::SpawnBombTosun, 10, true, 3);
	GetWorldTimerManager().SetTimer(BigTosunWaitHandle, this, &ASurvivalGameMode::SpawnBigTosun, 40, true, 40);

	VictoryAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), VictoryMusic);
	FailedAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), FailedMusic);

	TosunSpawnPoints.Emplace(FVector(-221, 555, 691));
	TosunSpawnPoints.Emplace(FVector(-1270, 150, 691));
	TosunSpawnPoints.Emplace(FVector(-380, -210, 691));

	BombTosunSpawnPoints.Emplace(FVector(-220, -670, 691));
	BombTosunSpawnPoints.Emplace(FVector(220, 260, 691));
	BombTosunSpawnPoints.Emplace(FVector(-1350, 680, 691));
}

void ASurvivalGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASurvivalGameMode::SetVictoryMusic(bool bIsPlaying)
{
	if (VictoryAudioComponent != nullptr && bIsPlaying)
	{
		VictoryAudioComponent->Play();
		VictoryAudioComponent->FadeIn(3);
	}

	if (VictoryAudioComponent != nullptr && !bIsPlaying)
	{
		VictoryAudioComponent->FadeOut(3, 0);
	}
}

void ASurvivalGameMode::SetFailedMusic(bool bIsPlaying)
{
	if (FailedAudioComponent != nullptr && bIsPlaying)
	{
		FailedAudioComponent->Play();
		FailedAudioComponent->FadeIn(3);
	}

	if (FailedAudioComponent != nullptr && !bIsPlaying)
	{
		FailedAudioComponent->FadeOut(3, 0);
	}
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

	TArray<FVector> SpawnPoints = TosunSpawnPoints;
	int32 RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn == nullptr) return;

	while ((Pawn->GetActorLocation() - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
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

	TArray<FVector> SpawnPoints = BombTosunSpawnPoints;
	int32 RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn == nullptr) return;

	while ((Pawn->GetActorLocation() - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
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

	TArray<FVector> SpawnPoints = TosunSpawnPoints;
	int32 RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);

	APawn* Pawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	if (Pawn == nullptr) return;

	while ((Pawn->GetActorLocation() - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);

	Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);
}

void ASurvivalGameMode::PlayStarting()
{
	UGameplayStatics::PlaySound2D(GetWorld(), Starting);

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::PlayMissionStart, 2, false);
}

void ASurvivalGameMode::PlayMissionStart()
{
	UGameplayStatics::PlaySound2D(GetWorld(), MissionStart);

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::PlayHalfWay, FMath::RandRange(59.f, 61.f), false);
}

void ASurvivalGameMode::PlayHalfWay()
{
	UGameplayStatics::PlaySound2D(GetWorld(), HalfWay);

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::PlayAlmostDone, FMath::RandRange(21.f, 23.f), false);
}

void ASurvivalGameMode::PlayAlmostDone()
{
	UGameplayStatics::PlaySound2D(GetWorld(), AlmostDone);

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::PlayGoGoGo, FMath::RandRange(18.f, 20.f), false);
}

void ASurvivalGameMode::PlayGoGoGo()
{
	if (GoGoGoCount >= 3) return;

	UGameplayStatics::PlaySound2D(GetWorld(), GoGoGo);

	FTimerHandle WaitHandle;
	GetWorldTimerManager().SetTimer(WaitHandle, this, &ASurvivalGameMode::PlayGoGoGo, 7, false);

	GoGoGoCount++;
}