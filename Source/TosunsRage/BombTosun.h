// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy.h"
#include "BombTosun.generated.h"

/**
 * 
 */
UCLASS()
class TOSUNSRAGE_API ABombTosun : public AEnemy
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;

public:
	virtual void Attack() override;

private:
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* Explosion;

	UPROPERTY(EditDefaultsOnly)
	USoundBase* ExplosionSound;
};
