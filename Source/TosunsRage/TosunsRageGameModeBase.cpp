// Copyright Epic Games, Inc. All Rights Reserved.


#include "TosunsRageGameModeBase.h"
#include "Kismet/GameplayStatics.h"

void ATosunsRageGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (PlayerController != nullptr) PlayerController->SetShowMouseCursor(false);
}