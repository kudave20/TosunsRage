// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EscapeWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UEscapeWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Escape;

	UPROPERTY(meta = (BindWidget))
	class UButton* Retry;

	UPROPERTY(meta = (BindWidget))
	UButton* Resume;

	UPROPERTY(meta = (BindWidget))
	UButton* MainMenu;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> FadeWidgetClass;

	UPROPERTY()
	UUserWidget* FadeWidget;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* RetrySound;

	UFUNCTION()
	void ResumeOnRelease();

	UFUNCTION()
	void RetryOnRelease();

	UFUNCTION()
	void MainMenuOnRelease();

	UFUNCTION()
	void LevelRetry();

	UFUNCTION()
	void OpenMainMenu();

	void GameOverSet();

	void RadioChat(USoundBase* SoundBase);
};
