// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GProjectile.generated.h"

UCLASS()
class GGAME_API AGProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Konstruktor.
	AGProjectile();
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

	// Ustaw w³aœcicela pocisku
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		void SetProjectileOwner(class AGCharacter * ProjectileOwner);

	// Pobierz w³aœcicela
	UFUNCTION(BlueprintCallable, Category = "GProjectile")
		class AGCharacter * GetProjectileOwner();

	//Metoda do oslugi replikacji [silnik]
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;

	/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	/// Zmienne
	/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	//W³aœciciel pocisku
	UPROPERTY(Replicated)
		class AGCharacter * ProjectileOwner;

protected:

public:
	UPROPERTY(Replicated, EditAnywhere)
		int Damage;

	UPROPERTY(Replicated, EditAnywhere)
		FVector Offset;

	// Komponent kuli z kolizja
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class USphereComponent * CollisionComponent;

	// Komponenty poruszania sie pocisku 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		class UProjectileMovementComponent * ProjectileMovementComponent;

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent * ActorMeshComponent;
};
