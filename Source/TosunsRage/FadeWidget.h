// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "FadeWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UFadeWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void FadeIn();
	void FadeOut();

private:
	UPROPERTY(Transient, meta = (BindWidgetAnim))
	UWidgetAnimation* FadeEffect;
};
