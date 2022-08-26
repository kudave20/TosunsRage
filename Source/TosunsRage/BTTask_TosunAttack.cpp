// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TosunAttack.h"
#include "AIController.h"
#include "Tosun.h"

UBTTask_TosunAttack::UBTTask_TosunAttack()
{
	NodeName = TEXT("Tosun Attack");
}

EBTNodeResult::Type UBTTask_TosunAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	ATosun* Enemy = Cast<ATosun>(OwnerComp.GetAIOwner()->GetPawn());
	
	if (Enemy == nullptr) return EBTNodeResult::Failed;

	Enemy->Attack();

	return EBTNodeResult::Succeeded;
}