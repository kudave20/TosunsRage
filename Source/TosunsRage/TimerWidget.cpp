// Fill out your copyright notice in the Description page of Project Settings.


#include "TimerWidget.h"
#include "ShooterPlayerController.h"
#include "Components/TextBlock.h"

void UTimerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle WaitHandle;
	GetWorld()->GetTimerManager().SetTimer(WaitHandle, this, &UTimerWidget::SetCurrentTimer, 1, true);

	Minute->TextDelegate.BindUFunction(this, "SetMinute");
	Second->TextDelegate.BindUFunction(this, "SetSecond");
}

void UTimerWidget::SetCurrentTimer()
{
	if (Sec == 0)
	{
		if (Min == 0)
		{
			// Victory
			AShooterPlayerController* PlayerController = GetOwningPlayer<AShooterPlayerController>();
			if (PlayerController != nullptr) PlayerController->GameHasEnded(PlayerController->GetPawn(), true);
		}
		else
		{
			Min--;
			Sec = 59;
		}
	}
	else Sec--;
}

FText UTimerWidget::SetMinute()
{
	if (Min < 10)
	{
		FString String = TEXT("0") + FString::FromInt(Min);
		return FText::FromString(String);
	}

	return FText::AsNumber(Min);
}

FText UTimerWidget::SetSecond()
{
	if (Sec < 10)
	{
		FString String = TEXT("0") + FString::FromInt(Sec);
		return FText::FromString(String);
	}

	return FText::AsNumber(Sec);
}