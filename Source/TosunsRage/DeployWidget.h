// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DeployWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UDeployWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativeConstruct() override;

public:
	virtual bool Initialize() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UButton* FirstTip;

	UPROPERTY(meta = (BindWidget))
	UButton* SecondTip;

	UPROPERTY(meta = (BindWidget))
	UButton* ThirdTip;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Second;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Millisecond;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* Survival;

	UPROPERTY(EditDefaultsOnly)
	int32 Sec = 7;

	UPROPERTY(EditDefaultsOnly)
	int32 Millisec = 0;

	void SetTipVisible();

	void PlayMusic();

	void SetDeployTimer();

	UFUNCTION()
	FText SetSecond();

	UFUNCTION()
	FText SetMillisecond();
};
