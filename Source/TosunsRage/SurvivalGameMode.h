// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TosunsRageGameModeBase.h"
#include "GameFramework/Character.h"
#include "SurvivalGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API ASurvivalGameMode : public ATosunsRageGameModeBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
public:
	void SetVictoryMusic(bool bIsPlaying);

	void SetFailedMusic(bool bIsPlaying);

	void SetIsGameOver(bool bIsGameOver);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> Tosun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> BombTosun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> BigTosun;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AK74PickUp;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> MP5PickUp;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* VictoryMusic;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* FailedMusic;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* Starting;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* MissionStart;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* HalfWay;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* AlmostDone;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* GoGoGo;

	UPROPERTY(EditAnywhere)
	TArray<FVector> TosunSpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<FVector> BombTosunSpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<FVector> AK74SpawnPoints;

	UPROPERTY(EditAnywhere)
	TArray<FVector> MP5SpawnPoints;

	int32 GoGoGoCount;

	bool IsGameOver;

	UAudioComponent* VictoryAudioComponent;
	UAudioComponent* FailedAudioComponent;

	FTimerHandle TosunWaitHandle;
	FTimerHandle BombTosunWaitHandle;
	FTimerHandle BigTosunWaitHandle;

	FTimerHandle AK74WaitHandle;
	FTimerHandle MP5WaitHandle;

	void SpawnTosun();
	void SpawnBombTosun();
	void SpawnBigTosun();

	void SpawnAK74();
	void SpawnMP5();

	void PlayStarting();
	void PlayMissionStart();
	void PlayHalfWay();
	void PlayAlmostDone();
	void PlayGoGoGo();
};
