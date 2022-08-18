// Fill out your copyright notice in the Description page of Project Settings.


#include "TosunAIController.h"
#include "Kismet/GameplayStatics.h"

void ATosunAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    SetFocus(PlayerPawn);
    MoveToActor(PlayerPawn, AcceptanceRadius);
}
