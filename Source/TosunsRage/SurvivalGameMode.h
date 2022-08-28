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
	virtual void Tick(float DeltaTime) override;

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

	int32 GoGoGoCount;

	bool IsGameOver;

	UAudioComponent* VictoryAudioComponent;
	UAudioComponent* FailedAudioComponent;

	FTimerHandle TosunWaitHandle;
	FTimerHandle BombTosunWaitHandle;
	FTimerHandle BigTosunWaitHandle;

	void SpawnTosun();
	void SpawnBombTosun();
	void SpawnBigTosun();

	void PlayStarting();
	void PlayMissionStart();
	void PlayHalfWay();
	void PlayAlmostDone();
	void PlayGoGoGo();
};
