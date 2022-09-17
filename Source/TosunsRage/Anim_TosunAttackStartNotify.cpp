// Fill out your copyright notice in the Description page of Project Settings.


#include "Anim_TosunAttackStartNotify.h"
#include "Tosun.h"

void UAnim_TosunAttackStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	ATosun* Enemy = Cast<ATosun>(MeshComp->GetOwner());

	if (Enemy != nullptr) Enemy->AttackStart();
}