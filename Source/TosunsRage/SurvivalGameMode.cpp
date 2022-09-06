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

	GetWorldTimerManager().SetTimer(AK74WaitHandle, this, &ASurvivalGameMode::SpawnAK74, 30, true, 30);
	GetWorldTimerManager().SetTimer(MP5WaitHandle, this, &ASurvivalGameMode::SpawnMP5, 30, true, 30);

	VictoryAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), VictoryMusic);
	FailedAudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), FailedMusic);
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

	FVector PawnLocation = Pawn->GetActorLocation();

	if (PawnLocation.Z < 488)
	{
		for (FVector SpawnPoint : SpawnPoints)
		{
			SpawnPoint.Z = 256;
		}
	}

	while ((PawnLocation - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(Tosun, Location, Rotation);

	if (PawnLocation.Z < 488) Location.Z = 691;
	else Location.Z = 256;

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

	FVector PawnLocation = Pawn->GetActorLocation();

	if (PawnLocation.Z < 488)
	{
		for (FVector SpawnPoint : SpawnPoints)
		{
			SpawnPoint.Z = 256;
		}
	}

	while ((PawnLocation - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(BombTosun, Location, Rotation);

	if (PawnLocation.Z < 488) Location.Z = 691;
	else Location.Z = 256;

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

	FVector PawnLocation = Pawn->GetActorLocation();

	if (PawnLocation.Z < 488)
	{
		for (FVector SpawnPoint : SpawnPoints)
		{
			SpawnPoint.Z = 256;
		}
	}

	while ((PawnLocation - SpawnPoints[RandomInt]).Size() <= 500)
	{
		SpawnPoints.RemoveAt(RandomInt);

		if (SpawnPoints.Num() == 0) return;

		RandomInt = FMath::RandRange(0, SpawnPoints.Num() - 1);
	}

	FVector Location = SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);

	if (PawnLocation.Z < 488) Location.Z = 691;
	else Location.Z = 256;

	GetWorld()->SpawnActor<AActor>(BigTosun, Location, Rotation);
}

void ASurvivalGameMode::SpawnAK74()
{
	if (AK74SpawnPoints.Num() == 0) return;

	int32 RandomInt = FMath::RandRange(0, AK74SpawnPoints.Num() - 1);

	FVector Location = AK74SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(AK74PickUp, Location, Rotation);

	AK74SpawnPoints.RemoveAt(RandomInt);
}

void ASurvivalGameMode::SpawnMP5()
{
	if (MP5SpawnPoints.Num() == 0) return;

	int32 RandomInt = FMath::RandRange(0, MP5SpawnPoints.Num() - 1);

	FVector Location = MP5SpawnPoints[RandomInt];
	FRotator Rotation;

	GetWorld()->SpawnActor<AActor>(MP5PickUp, Location, Rotation);

	MP5SpawnPoints.RemoveAt(RandomInt);
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