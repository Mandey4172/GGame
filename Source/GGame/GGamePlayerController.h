// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "GGamePlayerController.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API AGGamePlayerController : public APlayerController
{
	GENERATED_BODY()

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void ScorePoint();
		bool ScorePoint_Validate() { return true; };
		void ScorePoint_Implementation();
	//Metoda do oslugi replikacji [silnik]
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const;
};
