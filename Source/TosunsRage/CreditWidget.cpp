// Fill out your copyright notice in the Description page of Project Settings.


#include "CreditWidget.h"
#include "Components/Button.h"

void UCreditWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Back->OnReleased.IsBound()) Back->OnReleased.AddDynamic(this, &UCreditWidget::BackOnRelease);
}

void UCreditWidget::BackOnRelease()
{
	RemoveFromParent();

	MainMenuWidget = CreateWidget(this, MainMenuWidgetClass);
	if (MainMenuWidget != nullptr) MainMenuWidget->AddToViewport();
}