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

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ACharacter> Tosun;

	bool IsGameOver;

	void SpawnTosun();
};
