// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "GDefaultsSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API UGDefaultsSaveGame : public USaveGame
{
	GENERATED_BODY()
public:

	UGDefaultsSaveGame( const FObjectInitializer & ObjectInitializer );

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GDefaultsSG)
		TArray<FString> ProfileList;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GDefaultsSG)
		bool AutoLogin;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GDefaultsSG)
		FString DefaultProfile;
};
