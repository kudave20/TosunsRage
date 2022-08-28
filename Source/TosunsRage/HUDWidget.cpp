// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Image.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/TextBlock.h"
#include "ShooterCharacter.h"
#include "Gun.h"

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	FTimerHandle CrossHairWaitHandle;
	GetWorld()->GetTimerManager().SetTimer(CrossHairWaitHandle, this, &UHUDWidget::SetCrossHair, 0.01f, true);

	FTimerHandle HideWaitHandle;
	GetWorld()->GetTimerManager().SetTimer(HideWaitHandle, this, &UHUDWidget::Hide, 0.01f, true);

	Health->TextDelegate.BindUFunction(this, "SetHealth");
	MaxAmmo->TextDelegate.BindUFunction(this, "SetMaxAmmo");
	Ammo->TextDelegate.BindUFunction(this, "SetAmmo");
}

void UHUDWidget::SetCrossHair()
{
	UCanvasPanelSlot* CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrossHairTop);

	APawn* Pawn = GetOwningPlayerPawn();

	if (Pawn == nullptr) return;

	float Speed = Pawn->GetVelocity().Size();
	float YValue = 0;

	if (CanvasPanelSlot != nullptr)
	{
		float InterpValue = FMath::FInterpTo<float>(CanvasPanelSlot->GetPosition().Y, -Speed, GetWorld()->GetDeltaSeconds(), 15);
		YValue = FMath::Clamp<float>(InterpValue, -200, -25);
		CanvasPanelSlot->SetPosition(FVector2D(0, YValue));
	}

	CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrossHairBottom);

	if (CanvasPanelSlot != nullptr)
	{
		CanvasPanelSlot->SetPosition(FVector2D(0, -YValue));
	}

	CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrossHairLeft);
	
	float XValue = 0;

	if (CanvasPanelSlot != nullptr)
	{
		float InterpValue = FMath::FInterpTo<float>(CanvasPanelSlot->GetPosition().X, -Speed, GetWorld()->GetDeltaSeconds(), 15);
		XValue = FMath::Clamp<float>(InterpValue, -200, -25);
		CanvasPanelSlot->SetPosition(FVector2D(XValue, 0));
	}

	CanvasPanelSlot = UWidgetLayoutLibrary::SlotAsCanvasSlot(CrossHairRight);

	if (CanvasPanelSlot != nullptr)
	{
		CanvasPanelSlot->SetPosition(FVector2D(-XValue, 0));
	}
}

void UHUDWidget::Hide()
{
	AShooterCharacter* ShooterCharacter = GetOwningPlayerPawn<AShooterCharacter>();

	if (ShooterCharacter == nullptr) return;

	if (ShooterCharacter->GetIsAiming())
	{
		CrossHairTop->SetVisibility(ESlateVisibility::Hidden);
		CrossHairBottom->SetVisibility(ESlateVisibility::Hidden);
		CrossHairRight->SetVisibility(ESlateVisibility::Hidden);
		CrossHairLeft->SetVisibility(ESlateVisibility::Hidden);
	}
	else
	{
		CrossHairTop->SetVisibility(ESlateVisibility::Visible);
		CrossHairBottom->SetVisibility(ESlateVisibility::Visible);
		CrossHairRight->SetVisibility(ESlateVisibility::Visible);
		CrossHairLeft->SetVisibility(ESlateVisibility::Visible);
	}
}

FText UHUDWidget::SetHealth()
{
	AShooterCharacter* ShooterCharacter = GetOwningPlayerPawn<AShooterCharacter>();

	if (ShooterCharacter == nullptr) return FText::AsNumber(0);

	float HealthValue = ShooterCharacter->GetHealth();
	FText HealthText = FText::AsNumber(HealthValue);

	return HealthText;
}

FText UHUDWidget::SetMaxAmmo()
{
	AShooterCharacter* ShooterCharacter = GetOwningPlayerPawn<AShooterCharacter>();

	if (ShooterCharacter == nullptr) return FText::AsNumber(0);

	AGun* CurrentGun = ShooterCharacter->GetCurrentGun();

	if (CurrentGun != nullptr)
	{
		int32 MaxAmmoValue = CurrentGun->GetMaxAmmo();
		FText MaxAmmoText = FText::AsNumber(MaxAmmoValue);

		return MaxAmmoText;
	}
	
	return FText::AsNumber(0);
}

FText UHUDWidget::SetAmmo()
{
	AShooterCharacter* ShooterCharacter = GetOwningPlayerPawn<AShooterCharacter>();

	if (ShooterCharacter == nullptr) return FText::AsNumber(0);

	AGun* CurrentGun = ShooterCharacter->GetCurrentGun();

	if (CurrentGun != nullptr)
	{
		int32 AmmoValue = CurrentGun->GetAmmo();
		FText AmmoText = FText::AsNumber(AmmoValue);

		return AmmoText;
	}

	return FText::AsNumber(0);
}