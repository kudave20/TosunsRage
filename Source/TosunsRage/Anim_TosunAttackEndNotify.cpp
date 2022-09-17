// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_TosunAttackEndNotify.h"
#include "Tosun.h"

void UAnim_TosunAttackEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATosun* Enemy = Cast<ATosun>(MeshComp->GetOwner());

	if (Enemy != nullptr) Enemy->AttackEnd();
}