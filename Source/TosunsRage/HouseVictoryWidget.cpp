// Fill out your copyright notice in the Description page of Project Settings.


#include "HouseVictoryWidget.h"
#include "SurvivalGameMode.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "FadeWidget.h"

void UHouseVictoryWidget::NativeConstruct()
{
	Super::NativeConstruct();

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();

	if (SurvivalGameMode != nullptr) SurvivalGameMode->SetVictoryMusic(true);

	PlayAnimation(Victory);

	if (!MainMenu->OnReleased.IsBound()) MainMenu->OnReleased.AddDynamic(this, &UHouseVictoryWidget::MainMenuOnRelease);
	if (!Next->OnReleased.IsBound()) Next->OnReleased.AddDynamic(this, &UHouseVictoryWidget::NextOnRelease);
}

void UHouseVictoryWidget::MainMenuOnRelease()
{
	VictorySet();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OpenMainMenu";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 5, LatentInfo);
}

void UHouseVictoryWidget::NextOnRelease()
{
	VictorySet();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OpenMainMenu";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 5, LatentInfo);

	// Next level will be developed.
}

void UHouseVictoryWidget::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UHouseVictoryWidget::VictorySet()
{
	FadeWidget = CreateWidget(this, FadeWidgetClass);

	if (FadeWidget != nullptr)
	{
		FadeWidget->AddToViewport();

		UFadeWidget* Widget = Cast<UFadeWidget>(FadeWidget);

		if (Widget != nullptr) Widget->FadeOut();
	}

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();

	if (SurvivalGameMode != nullptr) SurvivalGameMode->SetVictoryMusic(false);
}