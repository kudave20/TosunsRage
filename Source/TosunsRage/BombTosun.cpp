// Fill out your copyright notice in the Description page of Project Settings.


#include "BombTosun.h"
#include "Kismet/GameplayStatics.h"
#include "ShooterCharacter.h"

void ABombTosun::Attack()
{
	Super::Attack();

	IsAttacking = true;

	FVector Direction = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation() - GetActorLocation();

	FVector Start = GetActorLocation();
	FVector End = GetActorLocation() + Direction;

	SphereTrace(Direction, Start, End);

	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), Explosion, GetActorLocation());
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ExplosionSound, GetActorLocation());

	Die();
}