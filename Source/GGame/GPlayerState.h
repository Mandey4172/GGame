// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "GPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API AGPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:

	AGPlayerState();

	UPROPERTY(Replicated, VisibleAnywhere)
		int PlayerScore;

	UFUNCTION(BlueprintCallable)
	void ScorePoint();
	//Metoda do oslugi replikacji [silnik]
	//void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	//UFUNCTION(BlueprintCallable, Category = "Save/Load Game")
	//void SetSaveGame(class UGProfileSaveGame * NSaveGame);

	//UFUNCTION( BlueprintCallable, Category = "Save/Load Game" )
	//class UGProfileSaveGame * GetSaveGame();

	////Save
	//UPROPERTY(EditAnywhere, Category = Save)
	//TSubclassOf<class UGProfileSaveGame> CharacterSaveGameClass;

	////SaveHandle
	//UPROPERTY(VisibleAnywhere)
	//class UGProfileSaveGame * CharacterSaveGame;
};
