// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API AShooterPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;

public:
	virtual void GameHasEnded(class AActor* EndGameFocus = nullptr, bool bIsWinner = false) override;

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> HUDClass;

	UUserWidget* HUD;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> FadeWidgetClass;

	UUserWidget* FadeWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> VictoryWidgetClass;

	UUserWidget* VictoryWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> GameOverWidgetClass;

	UUserWidget* GameOverWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<class UUserWidget> TimerWidgetClass;

	UUserWidget* TimerWidget;

	UPROPERTY(EditAnywhere)
	USoundBase* MissionAccomplishedSound;

	UPROPERTY(EditAnywhere)
	USoundBase* MissionFailedSound;

	void VictorySet();

	void GameOverSet();
};
