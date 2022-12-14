// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_TosunAttack.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UBTTask_TosunAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_TosunAttack();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
