// Fill out your copyright notice in the Description page of Project Settings.


#include "GameOverWidget.h"
#include "Components/Button.h"
#include "SurvivalGameMode.h"
#include "FadeWidget.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void UGameOverWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(GameOverEffect);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "SetButtonVisible";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 2.5f, LatentInfo);

	if (!Retry->OnReleased.IsBound()) Retry->OnReleased.AddDynamic(this, &UGameOverWidget::RetryOnRelease);
	if (!MainMenu->OnReleased.IsBound()) MainMenu->OnReleased.AddDynamic(this, &UGameOverWidget::MainMenuOnRelease);
}

void UGameOverWidget::SetButtonVisible()
{
	Retry->SetVisibility(ESlateVisibility::Visible);
	MainMenu->SetVisibility(ESlateVisibility::Visible);
}

void UGameOverWidget::RetryOnRelease()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (PlayerController == nullptr) return;

	FadeWidget = CreateWidget(PlayerController, FadeWidgetClass);

	if (FadeWidget != nullptr)
	{
		FadeWidget->AddToViewport();

		UFadeWidget* Widget = Cast<UFadeWidget>(FadeWidget);

		if (Widget != nullptr) Widget->FadeOut();
	}

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();
	
	if (SurvivalGameMode != nullptr) SurvivalGameMode->SetFailedMusic(false);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "LevelRetry";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 3, LatentInfo);
}

void UGameOverWidget::MainMenuOnRelease()
{
	APlayerController* PlayerController = GetOwningPlayer();

	if (PlayerController == nullptr) return;

	FadeWidget = CreateWidget(PlayerController, FadeWidgetClass);

	if (FadeWidget != nullptr)
	{
		FadeWidget->AddToViewport();

		UFadeWidget* Widget = Cast<UFadeWidget>(FadeWidget);

		if (Widget != nullptr) Widget->FadeOut();
	}

	ASurvivalGameMode* SurvivalGameMode = GetWorld()->GetAuthGameMode<ASurvivalGameMode>();

	if (SurvivalGameMode != nullptr) SurvivalGameMode->SetFailedMusic(false);

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "ToMainMenu";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 5, LatentInfo);
}

void UGameOverWidget::LevelRetry()
{
	RadioChat(RetrySound);

	APlayerController* PlayerController = GetOwningPlayer();

	if (PlayerController != nullptr) PlayerController->RestartLevel();
}

void UGameOverWidget::ToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UGameOverWidget::RadioChat(USoundBase* SoundBase)
{
	UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), SoundBase);

	if (AudioComponent != nullptr) AudioComponent->Play();
}