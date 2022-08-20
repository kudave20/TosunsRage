// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_AttackStop.h"
#include "AIController.h"
#include "Enemy.h"

UBTTask_AttackStop::UBTTask_AttackStop()
{
    NodeName = TEXT("Attack Stop");
}


EBTNodeResult::Type UBTTask_AttackStop::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    AEnemy* Enemy = Cast<AEnemy>(OwnerComp.GetAIOwner()->GetPawn());

    Enemy->SetIsAttacking(false);

    return EBTNodeResult::Succeeded;
}