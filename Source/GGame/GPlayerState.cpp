// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GPlayerState.h"
#include "GCharacter.h"
#include "GGameInstance.h"

AGPlayerState::AGPlayerState()
{
	Score = 0;
}
void AGPlayerState::ScorePoint()
{
	Score++;
	if (Score > 2)
	{
		if (GEngine)
			GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, TEXT("END GAME"));
		if (this->HasAuthority())
		{
			if (GetWorld())
			{
				//GetWorld()->ServerTravel(FString("/GGame/Lobby/End"),true);
				GetWorld()->Exec(GetWorld(), TEXT("ServerTravel /GGame/Lobby/End?listen "));
			}
		}
	}
		
}
/*	*/
//void AGPlayerState::SetSaveGame( class UGProfileSaveGame * NSaveGame)
//{
//	CharacterSaveGame =  NSaveGame;
//}
///*	*/
//class UGProfileSaveGame * AGPlayerState::GetSaveGame()
//{
//	return CharacterSaveGame;
//}
/*
void AGPlayerState::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGPlayerState, CharacterSaveGame);
}
*/
