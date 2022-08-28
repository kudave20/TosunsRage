// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TimerWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UTimerWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* Minute;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Second;

	int32 Min = 3;
	int32 Sec = 0;

	void SetCurrentTime();

	UFUNCTION()
	FText SetMinute();

	UFUNCTION()
	FText SetSecond();
};
