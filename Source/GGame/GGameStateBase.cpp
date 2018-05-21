// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GGameStateBase.h"
#include "UnrealNetwork.h"
#include "GPlayerState.h"

void AGGameStateBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FText AGGameStateBase::GetPlayerListText()
{
	return PlayerListText;
}
	
void AGGameStateBase::SetPlayerListText(FText PListText)
{
	this->PlayerListText = PListText;
}
//MEtoda do oslugi replikacji [silnik]
void AGGameStateBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGGameStateBase, PlayerListText);
}