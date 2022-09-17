// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_SplashNotify.h"
#include "BigTosun.h"

void UAnim_SplashNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ABigTosun* Enemy = Cast<ABigTosun>(MeshComp->GetOwner());

	if (Enemy != nullptr) Enemy->SplashAttack();
}