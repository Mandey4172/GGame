// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GExplosion.generated.h"

UCLASS()
class GGAME_API AGExplosion : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGExplosion();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "GExplosion")
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	// Ustaw w³aœcicela pocisku
	UFUNCTION(BlueprintCallable, Category = "GExplosion")
		void SetExplosionOwner(class AGCharacter * ExplosionOwner);

	// Pobierz w³aœcicela
	UFUNCTION(BlueprintCallable, Category = "GExplosion")
		class AGCharacter * GetExplosionOwner();

	//Metoda do oslugi replikacji [silnik]
	void GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const;
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
private:
	//W³aœciciel pocisku
	UPROPERTY(Replicated)
		class AGCharacter * ExplosionOwner;

public:
	UPROPERTY(Replicated, EditAnywhere)
		float Damage;

	UPROPERTY(Replicated, EditAnywhere)
		float ChangeOfRadius;

	UPROPERTY(Replicated, EditAnywhere)
		float MaximalRadius;

	// Komponent kuli z kolizja
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		USphereComponent * CollisionComponent;

	// Komponenty statycznej siatki 
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
		UStaticMeshComponent * ActorMeshComponent;
};
