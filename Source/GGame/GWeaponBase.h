// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GWeaponBase.generated.h"

UCLASS()
class GGAME_API AGWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGWeaponBase();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	/* Strzal broni */
	UFUNCTION()
		virtual void Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner);

	/* Pobierz czas do nastepnego wystrza³u */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float GetDelay();

	/* Prze³aduj broñ (zwraca czas prze³adowania ) */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		float Reload();

	/* Pobiera pojemnoœæ magazynku */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetMagazineSize();

	/* Pobiera ile kul jest w magazynku */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetBulletsInMaggazie();

	/* Pobierz obra¿enia kuli*/
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		int GetDamage();

	/* Aktualizuj rozrzut */
	UFUNCTION(BlueprintCallable, Category = "Weapon")
		virtual void UpdateRecoil(float DeltaTime);

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
protected:
	/* Czas wystrzalu */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float Delay;

	/* Aktualna ilosc naboji */
	UPROPERTY(Replicated)
		int InMagazine;

	/* Polozenie wystrzalu pocisku */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
		FVector MuzzleOffset;
	
	/* Czas przeladowania */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float ReloadDelay;

	/* Obra¿enia */
	UPROPERTY(EditAnywhere, Category = Weapon)
		float Damage;

	/* Pojemnosc magazynku */
	UPROPERTY(Replicated, EditAnywhere, Category = Weapon)
		int MagazineSize;

public:

	/* Siatka broni */
	UPROPERTY(VisibleAnywhere, Category = Mesh)
		USkeletalMeshComponent * MeshComponent;

	/* Komponent kuli z kolizja */
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent * CollisionComponent;

	/* Pocisk broni */
	UPROPERTY(EditDefaultsOnly, Category = Weapon)
		TSubclassOf<class AGBullet> ProjectileClass;

};
