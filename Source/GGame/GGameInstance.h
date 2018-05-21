// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Runtime/UMG/Public/UMG.h"
#include "Runtime/UMG/Public/UMGStyle.h"
#include "Runtime/UMG/Public/Slate/SObjectWidget.h"
#include "Runtime/UMG/Public/IUMGModule.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Engine/GameInstance.h"
#include "GProfileSaveGame.h"
#include "GDefaultsSaveGame.h"
#include "GCharacter.h"
#include "GDefaultsSaveGame.h"
#include "GProfileSaveGame.h"
#include "GGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class GGAME_API UGGameInstance : public UGameInstance
{
	GENERATED_BODY()

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

protected:

public:

	/* Poka¿ Main Menu */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		void ShowMainMenu();

	/* Ukryj Main Menu */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		void HideMainMenu();

	/* Poka¿ Lobby */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		void ShowLobby();

	/* Ukryj Lobby */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		void HideLobby();

	/* Ustaw nazwê serwera */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		void SetServerName(FString ServerName);

	/* Pobierz nazwê serwera */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		FString GetServerName();

	/* Ustaw maksymalna liczbê graczy */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		void SetMaxPlayers(int MaxPlayers);

	/* Pobierz maksymalna liczbê graczy */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		int GetMaxPlayers();

	/* Zapisz zapis gracza */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		void SaveDefaultsSave();

	/* Wczytaj zapis gracza */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		class UGDefaultsSaveGame * LoadDefaultsSave();

	/* Zapisz zapis gracza */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		void SaveProfileSave();

	/* Wczytaj zapis gracza */
	UFUNCTION( BlueprintCallable, Category = "GGameInstance" )
		class UGProfileSaveGame * LoadProfileSave(FString ProfileName);

	/* Pobierz Defaults */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		class UGDefaultsSaveGame * GetDefaults();

	/* Pobierz profil */
	UFUNCTION(BlueprintCallable, Category = "GGameInstance")
		class UGProfileSaveGame * GetProfile();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

	/* Main Menu */
	UPROPERTY()
		UUserWidget * MainMenu;

	/* Lobby */
	UPROPERTY()
		UUserWidget * Lobby;

	UPROPERTY(EditAnywhere)
		int MaxPlayers;

	UPROPERTY(EditAnywhere)
		FString ServerName;

protected:

public:

	UPROPERTY(EditAnywhere)
		UGDefaultsSaveGame * Defaults;

	UPROPERTY(EditAnywhere)
		UGProfileSaveGame * Profile;

	/* Wybór Main Menu*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = GGameInstance)
	TSubclassOf<class UUserWidget> MainMenuClass;

	/* Wybór Main Menu*/
	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = GGameInstance )
	TSubclassOf<class UUserWidget> LobbyClass;

};
