// Fill out your copyright notice in the Description page of Project Settings.


#include "Tosun.h"
#include "Kismet/GameplayStatics.h"

void ATosun::Attack()
{
	Super::Attack();

	IsAttacking = true;

	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();
	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Direction;

	FTimerHandle WaitHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUFunction(this, FName("SphereTrace"), Direction, Start, End);
	
	GetWorldTimerManager().SetTimer(WaitHandle, TimerDelegate, 1, false);
}

