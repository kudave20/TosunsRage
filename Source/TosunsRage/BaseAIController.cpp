// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	if (AIBehavior != nullptr) RunBehaviorTree(AIBehavior);
}

void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

