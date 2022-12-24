// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	virtual bool Initialize() override;
	
private:
	UPROPERTY(meta = (BindWidget))
	class UImage* CrossHairTop;

	UPROPERTY(meta = (BindWidget))
	UImage* CrossHairBottom;

	UPROPERTY(meta = (BindWidget))
	UImage* CrossHairRight;

	UPROPERTY(meta = (BindWidget))
	UImage* CrossHairLeft;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Health;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxAmmo;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Ammo;

	void SetCrossHair();

	void Hide();

	UFUNCTION()
	FText SetHealth();

	UFUNCTION()
	FText SetMaxAmmo();

	UFUNCTION()
	FText SetAmmo();
};
