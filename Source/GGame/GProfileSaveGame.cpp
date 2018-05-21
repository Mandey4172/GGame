// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GProfileSaveGame.h"
#include "GCharacter.h"
#include "UnrealNetwork.h"


FString UGProfileSaveGame::GetName()
{
	return Name;
}

void UGProfileSaveGame::SetName(FString PlayerName)
{
	this->Name = PlayerName;
}

// UGSaveGame :: Avatar
UTexture2D * UGProfileSaveGame::GetAvatar()
{
    return Avatar;
}
void UGProfileSaveGame::SetAvatar(UTexture2D *  NewAvatar)
{
    Avatar = NewAvatar;
}
	
// UGSaveGame :: CharacterAvatar
UTexture2D * UGProfileSaveGame::GetCharacterAvatar()
{
    return CharacterAvatar;
}
void UGProfileSaveGame::SetCharacterAvatar(UTexture2D *  NewCharacterAvatar)
{
    CharacterAvatar = NewCharacterAvatar;
}
	
// UGSaveGame :: Character
class AGCharacter *  UGProfileSaveGame::GetCharacter()
{
    return Character;
}
void UGProfileSaveGame::SetCharacter(class AGCharacter * NewCharacter)
{
    Character = NewCharacter;
}
	
FString UGProfileSaveGame::GetStatus()
{
    return Status;
}
void UGProfileSaveGame::SetStatus(FString NewStatus)
{
    Status = NewStatus;
}

