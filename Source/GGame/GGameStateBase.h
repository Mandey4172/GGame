// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/GameStateBase.h"
#include "GGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API AGGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
public:

	// Metoda wywowylaca podczas koñca gry.
	virtual void Tick(float DeltaTime) override;

	//MEtoda do oslugi replikacji [silnik]
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	UFUNCTION( BlueprintCallable, Category = "GGame:: Player List" )
	FText GetPlayerListText();
	
	UFUNCTION( BlueprintCallable, Category = "GGame:: Player List" )
	void SetPlayerListText(FText PListText);

	UPROPERTY(Replicated, EditAnywhere)
	FText PlayerListText;

	UPROPERTY(EditAnywhere)
	FName ExitLevel;

	/*UFUNCTION(BlueprintCallable, Category = "GGame:: Player List")
		FText GetPlayerListText();

	UFUNCTION(BlueprintCallable, Category = "GGame:: Player List")
	void SetPlayerListText(FText PListText);

	UPROPERTY(Replicated, EditAnywhere)
	bool IsGameActive;*/
};
