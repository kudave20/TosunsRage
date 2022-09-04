// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenuGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

void AMainMenuGameMode::SetMainMenuMusic(bool bPlay)
{
	UAudioComponent* AudioComponent = UGameplayStatics::CreateSound2D(GetWorld(), BackgroundMusic);

	if (AudioComponent == nullptr) return;
	
	if (bPlay) AudioComponent->Play();
	else AudioComponent->FadeOut(6, 0);
}

void AMainMenuGameMode::BeginPlay()
{
	Super::BeginPlay();

	SetMainMenuMusic(true);
}