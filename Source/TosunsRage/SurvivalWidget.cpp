// Fill out your copyright notice in the Description page of Project Settings.


#include "SurvivalWidget.h"
#include "Components/Button.h"

void USurvivalWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!House->OnReleased.IsBound()) House->OnReleased.AddDynamic(this, &USurvivalWidget::HouseOnRelease);
	if (!Back->OnReleased.IsBound()) Back->OnReleased.AddDynamic(this, &USurvivalWidget::BackOnRelease);
}

void USurvivalWidget::HouseOnRelease()
{
	Back->SetVisibility(ESlateVisibility::Hidden);
	SelectMap->SetVisibility(ESlateVisibility::Hidden);
	House->SetVisibility(ESlateVisibility::Hidden);
	Survival->SetVisibility(ESlateVisibility::Hidden);

	Description->SetVisibility(ESlateVisibility::HitTestInvisible);

	Deploy();
}

void USurvivalWidget::BackOnRelease()
{
	RemoveFromParent();

	MainMenuWidget = CreateWidget(this, MainMenuWidgetClass);

	if (MainMenuWidget != nullptr) MainMenuWidget->AddToViewport();
}

void USurvivalWidget::Deploy()
{
	DeployWidget = CreateWidget(this, DeployWidgetClass);

	if (DeployWidget != nullptr) DeployWidget->AddToViewport();
}