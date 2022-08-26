// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_BigTosunAttack.h"
#include "AIController.h"
#include "BigTosun.h"

UBTTask_BigTosunAttack::UBTTask_BigTosunAttack()
{
	NodeName = TEXT("BigTosun Attack");
}

EBTNodeResult::Type UBTTask_BigTosunAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

	ABigTosun* Enemy = Cast<ABigTosun>(OwnerComp.GetAIOwner()->GetPawn());

	if (Enemy == nullptr) return EBTNodeResult::Failed;

	Enemy->Attack();

	return EBTNodeResult::Succeeded;
}