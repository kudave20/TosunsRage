// Fill out your copyright notice in the Description page of Project Settings.


#include "KeysWidget.h"
#include "Components/Button.h"

void UKeysWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Back->OnReleased.IsBound()) Back->OnReleased.AddDynamic(this, &UKeysWidget::BackOnRelease);
}

void UKeysWidget::BackOnRelease()
{
	RemoveFromParent();

	MainMenuWidget = CreateWidget(this, MainMenuWidgetClass);
	if (MainMenuWidget != nullptr) MainMenuWidget->AddToViewport();
}