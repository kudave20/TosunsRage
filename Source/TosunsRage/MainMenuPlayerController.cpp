// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuPlayerController.h"
#include "Blueprint/UserWidget.h"

void AMainMenuPlayerController::BeginPlay()
{
	Super::BeginPlay();

	MainMenu = CreateWidget(this, MainMenuClass);

	if (MainMenu != nullptr) MainMenu->AddToViewport();

	SetShowMouseCursor(true);
}