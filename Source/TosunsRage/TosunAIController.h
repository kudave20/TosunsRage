// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "TosunAIController.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API ATosunAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	float AcceptanceRadius = 200;
};
