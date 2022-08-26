// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_BombTosunAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UBTTask_BombTosunAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_BombTosunAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
