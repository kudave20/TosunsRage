// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuWidget.h"
#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (!Play->OnReleased.IsBound()) Play->OnReleased.AddDynamic(this, &UMainMenuWidget::PlayOnRelease);
	if (!SPCollision->OnHovered.IsBound()) SPCollision->OnHovered.AddDynamic(this, &UMainMenuWidget::SPCollisionOnHover);
	if (!SPCollision->OnUnhovered.IsBound()) SPCollision->OnUnhovered.AddDynamic(this, &UMainMenuWidget::SPCollisionOnUnHover);
	if (!SVCollision->OnHovered.IsBound()) SVCollision->OnHovered.AddDynamic(this, &UMainMenuWidget::SVCollisionOnHover);
	if (!SVCollision->OnUnhovered.IsBound()) SVCollision->OnUnhovered.AddDynamic(this, &UMainMenuWidget::SVCollisionOnUnHover);
	if (!SVCollision->OnReleased.IsBound()) SVCollision->OnReleased.AddDynamic(this, &UMainMenuWidget::SVCollisionOnRelease);
	if (!Main->OnClicked.IsBound()) Main->OnClicked.AddDynamic(this, &UMainMenuWidget::MainOnClick);
	if (!Credit->OnReleased.IsBound()) Credit->OnReleased.AddDynamic(this, &UMainMenuWidget::CreditOnRelease);
	if (!Keys->OnReleased.IsBound()) Keys->OnReleased.AddDynamic(this, &UMainMenuWidget::KeysOnRelease);
	if (!Exit->OnReleased.IsBound()) Exit->OnReleased.AddDynamic(this, &UMainMenuWidget::ExitOnRelease);
}

void UMainMenuWidget::PlayOnRelease()
{
	SinglePlay->SetVisibility(ESlateVisibility::Visible);
	Survival->SetVisibility(ESlateVisibility::Visible);
	SPShadow->SetVisibility(ESlateVisibility::Visible);
	SPCollision->SetVisibility(ESlateVisibility::Visible);
	SVShadow->SetVisibility(ESlateVisibility::Visible);
	SVCollision->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::SPCollisionOnHover()
{
	SPShadow->SetVisibility(ESlateVisibility::Hidden);
	MainShadow->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::SPCollisionOnUnHover()
{
	SPShadow->SetVisibility(ESlateVisibility::Visible);
	MainShadow->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::SVCollisionOnHover()
{
	SVShadow->SetVisibility(ESlateVisibility::Hidden);
	MainShadow->SetVisibility(ESlateVisibility::Visible);
}

void UMainMenuWidget::SVCollisionOnUnHover()
{
	SVShadow->SetVisibility(ESlateVisibility::Visible);
	MainShadow->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::SVCollisionOnRelease()
{
	RemoveFromParent();

	SurvivalWidget = CreateWidget(this, SurvivalWidgetClass);
	if (SurvivalWidget != nullptr) SurvivalWidget->AddToViewport();
}

void UMainMenuWidget::MainOnClick()
{
	SinglePlay->SetVisibility(ESlateVisibility::Hidden);
	Survival->SetVisibility(ESlateVisibility::Hidden);
	SPShadow->SetVisibility(ESlateVisibility::Hidden);
	SPCollision->SetVisibility(ESlateVisibility::Hidden);
	SVShadow->SetVisibility(ESlateVisibility::Hidden);
	SVCollision->SetVisibility(ESlateVisibility::Hidden);
}

void UMainMenuWidget::CreditOnRelease()
{
	RemoveFromParent();

	CreditWidget = CreateWidget(this, CreditWidgetClass);
	if (CreditWidget != nullptr) CreditWidget->AddToViewport();
}

void UMainMenuWidget::KeysOnRelease()
{
	RemoveFromParent();

	KeysWidget = CreateWidget(this, KeysWidgetClass);
	if (KeysWidget != nullptr) KeysWidget->AddToViewport();
}

void UMainMenuWidget::ExitOnRelease()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), GetOwningPlayer(), EQuitPreference::Quit, false);
}