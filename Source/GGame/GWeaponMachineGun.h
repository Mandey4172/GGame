// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GWeaponBase.h"
#include "GameFramework/Pawn.h"
#include "GWeaponMachineGun.generated.h"

UCLASS()
class GGAME_API AGWeaponMachineGun : public AGWeaponBase
{
	GENERATED_BODY()

public:
	// Konstruktor.
	AGWeaponMachineGun();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

protected:

	/* Metoda wywowylaca podczas dodania postaci do gry. */
	virtual void BeginPlay() override;

public:

	/* Pobierz aktualny rozrzut */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		float GetRecoil();
	
	/* Maksymalny rozrzut */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		float GetMaximalRecoil();
	
	/* Minimalny rozrzut */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		float GetMinimalRecoil();

	/* Czas potrzebny do osiagniecia maksymalnego rozrzutu */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		float GetTimeToReachMaximalRecoil();
	
	/* Czas z jakim spada rozrzut */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		float GetTimeToReachMinimalRecoil();

	/* Uaktualnia rozrzut broni */
	UFUNCTION(BlueprintCallable, Category = "Weapon" )
		virtual void UpdateRecoil(float DeltaTime) override;

	/* Strzal broni */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner) override;

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

protected:

	/* Rozrzut aktualny */
	UPROPERTY(Replicated)
		float Recoil;

	/* Rozrzut maksymalny */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float MaximalRecoil;

	/* Rozrzut maksymalny */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float MinimalRecoil;

	/* Czas potrzebny do osiagniecia maksymalnego rozrzutu */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float MaxRecoilTime;

	/* Czas potrzebny do osiagniecia minimalnego rozrzutu */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float MinRecoilTime;

public:
	
};
