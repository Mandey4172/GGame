// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GCharacter.h"

#include "UnrealNetwork.h"
#include "GameFramework/SaveGame.h"
#include "GProfileSaveGame.generated.h"


/**
 * 
 */
UCLASS()
class GGAME_API UGProfileSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	// PlayerInfo :: Name
	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		FString GetName();

	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		void SetName(FString PlayerName);
	
	// PlayerInfo :: Avatar
	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		UTexture2D * GetAvatar();

	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		void SetAvatar(UTexture2D *  Avatar);
	
	// PlayerInfo :: CharacterAvatar
	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		UTexture2D * GetCharacterAvatar();

	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		void SetCharacterAvatar(UTexture2D *  CharacterAvatar);
	
	// PlayerInfo :: Character
	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		class AGCharacter * GetCharacter();

	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		void SetCharacter(class AGCharacter * Character);
	
	// PlayerInfo :: Status
	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		FString GetStatus();

	UFUNCTION(BlueprintCallable, Category = "GSaveGame")
		void SetStatus(FString Status);

protected:
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GPlayerInfo)
		FString Name;
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GPlayerInfo)
		UTexture2D * Avatar;
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GPlayerInfo)
		UTexture2D * CharacterAvatar;
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GPlayerInfo)
		class AGCharacter * Character;
	/**/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = GPlayerInfo)
		FString Status;
};


