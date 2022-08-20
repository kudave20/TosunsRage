// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_AttackStop.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API UBTTask_AttackStop : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_AttackStop();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
