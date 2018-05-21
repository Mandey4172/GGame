// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GWeaponMachineGun.h"
#include "GWeaponShotGun.generated.h"


UCLASS()
class GGAME_API AGWeaponShotGun : public AGWeaponMachineGun
{
	GENERATED_BODY()
public:
	// Konstruktor.
	AGWeaponShotGun();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

protected:

public:
	/* Strzal broni */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner) override;

	/* Ustaw iloœæ kul na wystrzal*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	void SetProjectilesPerShoot( int ProjectilesPerShoot );

	/* Pobierz iloœæ kul na wystrzal */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	int GetProjectilesPerShoot();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:

protected:

	/* Iloœæ kul na wystrzal */
	UPROPERTY(EditAnywhere, Category = Weapon)
		int ProjectilesPerShoot;

public:
};
