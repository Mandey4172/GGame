// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "GameFramework/GameModeBase.h"
#include "GGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API AGGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
public:

	virtual void StartPlay() override;

};
