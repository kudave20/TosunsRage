// Fill out your copyright notice in the Description page of Project Settings.


#include "EscapeWidget.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "SurvivalGameMode.h"
#include "FadeWidget.h"
#include "Components/AudioComponent.h"

void UEscapeWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayAnimation(Escape);

	if (!Resume->OnReleased.IsBound()) Resume->OnReleased.AddDynamic(this, &UEscapeWidget::ResumeOnRelease);
	if (!Retry->OnReleased.IsBound()) Retry->OnReleased.AddDynamic(this, &UEscapeWidget::RetryOnRelease);
	if (!MainMenu->OnReleased.IsBound()) MainMenu->OnReleased.AddDynamic(this, &UEscapeWidget::MainMenuOnRelease);
}

void UEscapeWidget::ResumeOnRelease()
{
	RemoveFromParent();

	UGameplayStatics::SetGamePaused(GetWorld(), false);

	APlayerController* PlayerController = GetOwningPlayer();

	if (PlayerController != nullptr) PlayerController->SetShowMouseCursor(false);
}

void UEscapeWidget::RetryOnRelease()
{
	GameOverSet();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "LevelRetry";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 3, LatentInfo);
}

void UEscapeWidget::MainMenuOnRelease()
{
	GameOverSet();

	FLatentActionInfo LatentInfo;
	LatentInfo.CallbackTarget = this;
	LatentInfo.ExecutionFunction = "OpenMainMenu";
	LatentInfo.UUID = 123;
	LatentInfo.Linkage = 0;

	UKismetSystemLibrary::Delay(GetWorld(), 5, LatentInfo);
}

void UEscapeWidget::LevelRetry()
{
	RadioChat(RetrySound);

	APlayerController* PlayerController = GetOwningPlayer();

	if (PlayerController != nullptr) PlayerController->RestartLevel();
}

void UEscapeWidget::OpenMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UEscapeWidget::GameOverSet()
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
}

void UEscapeWidget::RadioChat(USoundBase* SoundBase)
{
	UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), SoundBase);

	if (AudioComponent != nullptr) AudioComponent->Play();
}