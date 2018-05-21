// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GProfileSaveGame.h"
#include "GDefaultsSaveGame.h"
#include "GCharacter.h"
#include "GGameInstance.h"
#include "GGameStateBase.h"
#include "GPlayerState.h"

#include "UnrealNetwork.h"

/* Poka¿ Main Menu */
void UGGameInstance::ShowMainMenu()
{
	if (!MainMenu)
	{
		MainMenu = CreateWidget<UUserWidget>(this, MainMenuClass);
	}
	if (MainMenu)
	{
		APlayerController * PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
		PController->bShowMouseCursor = true;
		if (PController)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Created !!!"));
		}
		MainMenu->AddToViewport(9000); // Z-order, aby rysowa³o na szczycie.
	}

}

/* Ukryj Main Menu */
void UGGameInstance::HideMainMenu()
{

	APlayerController * PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	PController->bShowMouseCursor = false;
	if (PController)
		MainMenu->RemoveFromViewport(); // Z-order, aby rysowa³o na szczycie.

}

/* Poka¿ Lobby */
void UGGameInstance::ShowLobby()
{
	if (!Lobby)
	{
		Lobby = CreateWidget<UUserWidget>(this, LobbyClass);
	}
	if (Lobby)
	{
		APlayerController * PController = GetWorld()->GetFirstPlayerController();
		if (PController)
		{
			PController->bShowMouseCursor = true;
		}
		Lobby->AddToViewport(8000); // Z-order, aby rysowa³o na szczycie.
	}

}

/* Ukryj Lobby */
void UGGameInstance::HideLobby()
{
	APlayerController * PController = GetWorld()->GetFirstPlayerController();
	if (PController)
	{
		PController->bShowMouseCursor = false;
	}
	Lobby->RemoveFromViewport(); // Z-order, aby rysowa³o na szczycie.

}

/* Ustaw nazwê serwera */
void UGGameInstance::SetServerName(FString  NewServerName)
{
	ServerName = NewServerName;
}

/* Pobierz nazwê serwera */
FString  UGGameInstance::GetServerName()
{
	return ServerName;
}

/* Ustaw maksymalna liczbê graczy */
void UGGameInstance::SetMaxPlayers(int NewMaxPlayers)
{
    MaxPlayers = NewMaxPlayers;
}

/* Pobierz maksymalna liczbê graczy */
int UGGameInstance::GetMaxPlayers()
{
    return MaxPlayers;
}

void UGGameInstance::SaveDefaultsSave()
{
	if (!Defaults)
		Defaults = Cast<UGDefaultsSaveGame>(UGameplayStatics::CreateSaveGameObject(UGDefaultsSaveGame::StaticClass()));

	UGameplayStatics::SaveGameToSlot(Defaults, FString(TEXT("Defaults")), 0);
}

UGDefaultsSaveGame * UGGameInstance::LoadDefaultsSave()
{
	Defaults = Cast<UGDefaultsSaveGame>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("Defaults")), 0));
	if(!Defaults)
		Defaults = Cast<UGDefaultsSaveGame>(UGameplayStatics::CreateSaveGameObject(UGDefaultsSaveGame::StaticClass()));
	return Defaults;
}

void UGGameInstance::SaveProfileSave()
{
	if (Profile)
	{
		FString ProfileName;
		ProfileName = Profile->GetName();
		bool exist = false;
		for (FString PName : Defaults->ProfileList)
		{
			if (ProfileName == PName)
				exist = true;
		}
		if (!exist)
		{
			Defaults->ProfileList.Add(ProfileName);
			SaveDefaultsSave();
		}
		UGameplayStatics::SaveGameToSlot(Profile, FString(TEXT("Profile_") + ProfileName), 0);
	}
}

UGProfileSaveGame * UGGameInstance::LoadProfileSave(FString ProfileName)
{
	Profile = Cast<UGProfileSaveGame>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("Profile_") + ProfileName), 0));
	if (!Profile)
	{
		Profile = Cast<UGProfileSaveGame>(UGameplayStatics::CreateSaveGameObject(UGProfileSaveGame::StaticClass()));
		Profile->SetName(ProfileName);
	}
		
	return Profile;
}

UGDefaultsSaveGame * UGGameInstance::GetDefaults()
{
	return Defaults;
}

UGProfileSaveGame * UGGameInstance::GetProfile()
{
	return Profile;
}

///* Zapisz zapis gracza */
//void UGGameInstance::SaveCharacterSave(class AGPlayerState * PlayerState)
//{
//	APlayerController* PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
//	UGProfileSaveGame * NSaveGame;
//	NSaveGame = PlayerState->GetSaveGame();
//	if (!NSaveGame && PlayerState->CharacterSaveGameClass)
//		NSaveGame = Cast<UGProfileSaveGame>(UGameplayStatics::CreateSaveGameObject(PlayerState->CharacterSaveGameClass));
//	if (PlayerState)
//		UGameplayStatics::SaveGameToSlot(NSaveGame, FString(TEXT("CharacterSave")), 0);
//}
//
///* Wczytaj zapis gracza */
//class UGProfileSaveGame * UGGameInstance::LoadCharacterSave()
//{
//	UGProfileSaveGame * LoadGameInstance = Cast<UGProfileSaveGame>(UGameplayStatics::CreateSaveGameObject(UGProfileSaveGame::StaticClass()));
//	LoadGameInstance = Cast<UGProfileSaveGame>(UGameplayStatics::LoadGameFromSlot(FString(TEXT("CharacterSave")), 0));
//	return LoadGameInstance;
//}


