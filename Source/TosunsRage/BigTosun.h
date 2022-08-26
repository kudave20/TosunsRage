// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BigTosun.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API ABigTosun : public AEnemy
{
	GENERATED_BODY()
	
public:
	virtual void Attack() override;
};
