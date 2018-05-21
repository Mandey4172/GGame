// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GDefaultsSaveGame.h"


UGDefaultsSaveGame::UGDefaultsSaveGame(const FObjectInitializer & ObjectInitializer )
: Super(ObjectInitializer)
{
	
	this->AutoLogin = false;
}