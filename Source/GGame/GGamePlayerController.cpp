// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GPlayerState.h"
#include "GGamePlayerController.h"
#include "UnrealNetwork.h"

void AGGamePlayerController::ScorePoint_Implementation()
{
	((AGPlayerState *)(this->PlayerState))->Score++;
}

void AGGamePlayerController::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
}
