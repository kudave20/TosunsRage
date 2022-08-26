// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Attack.h"
#include "AIController.h"
#include "Enemy.h"
#include "Tosun.h"
#include "BombTosun.h"

UBTTask_Attack::UBTTask_Attack()
{
    NodeName = TEXT("Attack");
}


EBTNodeResult::Type UBTTask_Attack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
    Super::ExecuteTask(OwnerComp, NodeMemory);

    if (OwnerComp.GetAIOwner() == nullptr) return EBTNodeResult::Failed;

    APawn* OwnerPawn = OwnerComp.GetAIOwner()->GetPawn();

    if (OwnerPawn->IsA(ATosun::StaticClass()))
    {
        ATosun* Enemy = Cast<ATosun>(OwnerPawn);

        if (Enemy == nullptr) return EBTNodeResult::Failed;

        Enemy->Attack();
    }
    else if (OwnerPawn->IsA(ABombTosun::StaticClass()))
    {
        ABombTosun* Enemy = Cast<ABombTosun>(OwnerPawn);

        if (Enemy == nullptr) return EBTNodeResult::Failed;

        Enemy->Attack();
    }

    return EBTNodeResult::Succeeded;
}
