// Fill out your copyright notice in the Description page of Project Settings.


#include "BigTosun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void ABigTosun::Attack()
{
	Super::Attack();

	IsAttacking = true;

	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Direction;

	FTimerHandle WaitHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SphereTrace"), Direction, Start, End);

	GetWorldTimerManager().SetTimer(WaitHandle, TimerDelegate, 1.5f, false);
}