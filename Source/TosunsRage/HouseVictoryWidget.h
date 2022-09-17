// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HouseVictoryWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UHouseVictoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* Victory;
	
	UPROPERTY(meta = (BindWidget))
	class UButton* MainMenu;

	UPROPERTY(meta = (BindWidget))
	UButton* Next;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> FadeWidgetClass;

	UPROPERTY()
	UUserWidget* FadeWidget;

	UFUNCTION()
	void MainMenuOnRelease();

	UFUNCTION()
	void NextOnRelease();

	UFUNCTION()
	void OpenMainMenu();
	
	void VictorySet();
};
