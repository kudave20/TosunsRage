// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KeysWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UKeysWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY()
	UUserWidget* MainMenuWidget;

	UPROPERTY(meta = (BindWidget))
	class UButton* Back;
	
	UFUNCTION()
	void BackOnRelease();
};
