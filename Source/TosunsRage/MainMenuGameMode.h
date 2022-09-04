// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TosunsRageGameModeBase.h"
#include "MainMenuGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API AMainMenuGameMode : public ATosunsRageGameModeBase
{
	GENERATED_BODY()
	
public:
	void SetMainMenuMusic(bool bPlay);
	
protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly)
	USoundBase* BackgroundMusic;
};
