// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> SurvivalWidgetClass;

	UPROPERTY()
	UUserWidget* SurvivalWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> CreditWidgetClass;

	UPROPERTY()
	UUserWidget* CreditWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> KeysWidgetClass;

	UPROPERTY()
	UUserWidget* KeysWidget;

	UPROPERTY(meta = (BindWidget))
	class UButton* Play;

	UPROPERTY(meta = (BindWidget))
	UButton* SinglePlay;

	UPROPERTY(meta = (BindWidget))
	UButton* Survival;

	UPROPERTY(meta = (BindWidget))
	UButton* SPShadow;

	UPROPERTY(meta = (BindWidget))
	UButton* SPCollision;

	UPROPERTY(meta = (BindWidget))
	UButton* SVShadow;

	UPROPERTY(meta = (BindWidget))
	UButton* SVCollision;

	UPROPERTY(meta = (BindWidget))
	UButton* Main;

	UPROPERTY(meta = (BindWidget))
	UButton* MainShadow;

	UPROPERTY(meta = (BindWidget))
	UButton* Credit;

	UPROPERTY(meta = (BindWidget))
	UButton* Keys;

	UPROPERTY(meta = (BindWidget))
	UButton* Exit;

	UFUNCTION()
	void PlayOnRelease();

	UFUNCTION()
	void SPCollisionOnHover();

	UFUNCTION()
	void SPCollisionOnUnHover();

	UFUNCTION()
	void SVCollisionOnHover();

	UFUNCTION()
	void SVCollisionOnUnHover();

	UFUNCTION()
	void SVCollisionOnRelease();

	UFUNCTION()
	void MainOnClick();

	UFUNCTION()
	void CreditOnRelease();

	UFUNCTION()
	void KeysOnRelease();

	UFUNCTION()
	void ExitOnRelease();
};
