// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "Blueprint/UserWidget.h"
#include "SurvivalGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "FadeWidget.h"

void AShooterPlayerController::BeginPlay()
{
    Super::BeginPlay();

	FadeWidget = CreateWidget(this, FadeWidgetClass);

	if (FadeWidget != nullptr)
	{
		FadeWidget->AddToViewport();

		UFadeWidget* Widget = Cast<UFadeWidget>(FadeWidget);

		if (Widget != nullptr) Widget->FadeIn();
	}

    HUD = CreateWidget(this, HUDClass);

    if (HUD != nullptr) HUD->AddToViewport();

	TimerWidget = CreateWidget(this, TimerWidgetClass);

	if (TimerWidget != nullptr) TimerWidget->AddToViewport();

	SetShowMouseCursor(false);
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
    Super::GameHasEnded(EndGameFocus, bIsWinner);

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();
	SurvivalGameMode->SetIsGameOver(true);

	HUD->RemoveFromViewport();
	TimerWidget->RemoveFromViewport();

	// Victory
	if (bIsWinner)
	{
		VictorySet();
	}
	// Lose
	else
	{
		FTimerHandle WaitHandle;
		GetWorldTimerManager().SetTimer(WaitHandle, this, &AShooterPlayerController::GameOverSet, 1, false);
	}
}

void AShooterPlayerController::VictorySet()
{
	VictoryWidget = CreateWidget(this, VictoryWidgetClass);

	if (VictoryWidget != nullptr) VictoryWidget->AddToViewport();

	SetShowMouseCursor(true);

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();
	SurvivalGameMode->SetVictoryMusic(true);

	UGameplayStatics::PlaySound2D(GetWorld(), MissionAccomplishedSound);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}

void AShooterPlayerController::GameOverSet()
{
	GameOverWidget = CreateWidget(this, GameOverWidgetClass);

	if (GameOverWidget != nullptr) GameOverWidget->AddToViewport();
	
	SetShowMouseCursor(true);

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();
	SurvivalGameMode->SetFailedMusic(true);

	UGameplayStatics::PlaySound2D(GetWorld(), MissionFailedSound);
	UGameplayStatics::SetGamePaused(GetWorld(), true);
}