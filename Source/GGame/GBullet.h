// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "GBullet.generated.h"

UCLASS()
class GGAME_API AGBullet : public AActor
{
	GENERATED_BODY()
	
public:	

	// Konstruktor.
	AGBullet();

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

private:

protected:
	// Metoda wywowylaca podczas dodania postaci do gry.
		virtual void BeginPlay() override;

public:	
	// Metoda wywowylana co klatke.
		virtual void Tick(float DeltaTime) override;

	// Metoda przygotowujaca pocisk do wystrzalu
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		void FireInDirection(const FVector& ShootDirection);

	// Metoda wywowylana podczas uderzenia
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		virtual void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	// Ustaw w�a�cicela pocisku
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		void SetProjectileOwner(AGCharacter * ProjectileOwner);
		
	// Pobierz w�a�cicela
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		AGCharacter * GetProjectileOwner();

	//Metoda do oslugi replikacji [silnik]
		void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	//W�a�ciciel pocisku
	UPROPERTY(Replicated)
		AGCharacter * ProjectileOwner;

protected:

public:
	// Komponent kuli z kolizja
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent * CollisionComponent;

	// Komponenty poruszania sie pocisku 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UProjectileMovementComponent * ProjectileMovementComponent;

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent * ActorMeshComponent;
};

