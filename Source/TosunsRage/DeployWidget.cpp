// Fill out your copyright notice in the Description page of Project Settings.


#include "DeployWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"
#include "MainMenuGameMode.h"

void UDeployWidget::NativeConstruct()
{
	Super::NativeConstruct();

	SetTipVisible();

	UGameplayStatics::PlaySound2D(GetWorld(), Survival);

	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &UDeployWidget::PlayMusic, 1.7f, false);

	FTimerHandle TimerWaitHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerWaitHandle, this, &UDeployWidget::SetDeployTimer, 0.01f, true);

	Second->TextDelegate.BindUFunction(this, "SetSecond");
	Millisecond->TextDelegate.BindUFunction(this, "SetMillisecond");
}

void UDeployWidget::SetTipVisible()
{
	int32 RandomInt = FMath::RandRange(0, 2);

	switch (RandomInt)
	{
		case 0:
			FirstTip->SetVisibility(ESlateVisibility::Visible);
			break;
		case 1:
			SecondTip->SetVisibility(ESlateVisibility::Visible);
			break;
		case 2:
			ThirdTip->SetVisibility(ESlateVisibility::Visible);
			break;
	}
}

void UDeployWidget::PlayMusic()
{
	AMainMenuGameMode* MainMenuGameMode = GetWorld()->GetAuthGameMode<AMainMenuGameMode>();

	if (MainMenuGameMode != nullptr) MainMenuGameMode->SetMainMenuMusic(false);
}

void UDeployWidget::SetDeployTimer()
{
	if (Millisec == 0)
	{
		if (Sec == 0) UGameplayStatics::OpenLevel(GetWorld(), TEXT("House"));
		else
		{
			Sec--;
			Millisec = 99;
		}
	}
	else Millisec--;
}

FText UDeployWidget::SetSecond()
{
	return FText::AsNumber(Sec);
}

FText UDeployWidget::SetMillisecond()
{
	if (Millisec < 10)
	{
		FString String = TEXT("0") + FString::FromInt(Millisec);
		return FText::FromString(String);
	}
	
	return FText::AsNumber(Millisec);
}