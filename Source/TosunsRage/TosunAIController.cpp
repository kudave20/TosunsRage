// Fill out your copyright notice in the Description page of Project Settings.


#include "TosunAIController.h"
#include "Enemy.h"

void ATosunAIController::BeginPlay()
{
    Super::BeginPlay();

    if (AIBehavior != nullptr) RunBehaviorTree(AIBehavior);
}

void ATosunAIController::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
}
