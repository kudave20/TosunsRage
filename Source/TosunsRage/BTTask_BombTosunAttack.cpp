// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BombTosunAttack.h"
#include "AIController.h"
#include "BombTosun.h"

UBTTask_BombTosunAttack::UBTTask_BombTosunAttack()
{
	NodeName = TEXT("BombTosun Attack");
}

EBTNodeResult::Type UBTTask_BombTosunAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	ABombTosun* Enemy = Cast<ABombTosun>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy == nullptr) return EBTNodeResult::Failed;

	Enemy->Attack();

	return EBTNodeResult::Succeeded;
}