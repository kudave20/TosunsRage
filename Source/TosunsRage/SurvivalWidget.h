// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API USurvivalWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* Back;

	UPROPERTY(meta = (BindWidget))
	UButton* SelectMap;

	UPROPERTY(meta = (BindWidget))
	UButton* House;

	UPROPERTY(meta = (BindWidget))
	UButton* Description;

	UPROPERTY(meta = (BindWidget))
	UButton* Survival;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	UUserWidget* MainMenuWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> DeployWidgetClass;

	UPROPERTY()
	UUserWidget* DeployWidget;

	UFUNCTION()
	void HouseOnRelease();

	UFUNCTION()
	void BackOnRelease();

	void Deploy();
};
