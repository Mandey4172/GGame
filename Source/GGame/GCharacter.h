// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GWeaponBase.h"
#include "GameFramework/Character.h"
#include "GCharacter.generated.h"

UCLASS()
class GGAME_API AGCharacter : public ACharacter
{
	GENERATED_BODY()

public:

	// Konstruktor.
	AGCharacter();
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Metody
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:

	// Metoda wywowylaca podczas dodania postaci do gry.
	virtual void BeginPlay() override;
	// Metoda wywowylaca podczas końca gry.
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	// Metoda wywowylana co klatke.
	virtual void Tick(float DeltaTime) override;

	//Metoda obslugujaca zadawanie obrazen postaci
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);

	/*UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual float ReceiveAnyDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser);*/
	
	// Metoda poruszajaca postac przod.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MoveForward(float Value);

	// Metoda poruszajaca postac prawo.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MoveRight(float Value);

	// Metoda 
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MouseWheelUp();
	
	// Metoda 
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void MouseWheelDown();

	// Metoda ustawiajaca flage skoku.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StartJump();

	// Metoda czyszczaca flage skoku.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StopJump();

	// Metoda ustawiajaca flage przeladowania broni.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StartReload();

	// Metoda czyszczaca flage przeladowania broni.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StopReload();

	// Metoda ustawiajaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StartSkillA();

	// Metoda czyszczaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StopSkillA();

	// Metoda ustawiajaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StartSkillB();

	// Metoda czyszczaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StopSkillB();

	// Metoda ustawiajaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StartSkillC();

	// Metoda czyszczaca flage umiejetności A.
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		virtual void StopSkillC();

	//Metoda pobierajaca broń postaci
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		AGWeaponBase * GetWeapon();

	//Metoda pobierajaca ilość HP postaci
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		float GetHealth();

	//Metoda pobierająca wynik meczu	//TODO:: Przenies do PlayerState
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		int GetScore();

	//Metoda dodająca punkt do wyniku	//TODO:: Przenies do PlayerState
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
		void ScorePoint();

	// Funkcja ustawiajaca input.
	virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;
	
	//Metoda
	UFUNCTION(NetMulticast, Reliable, WithValidation)
		void SwapWeapon(float Value);
	bool SwapWeapon_Validate(float Value) { return true; };
	void SwapWeapon_Implementation(float Value);

	//Rozpoczecie strzelania
	UFUNCTION(Server, Reliable, WithValidation)
		void FireStart();
	bool FireStart_Validate() { return true; };
	void FireStart_Implementation();

	//Zakonczenie strzelania
	UFUNCTION(Server, Reliable, WithValidation)
		void FireStop();
	bool FireStop_Validate() { return true; };
	void FireStop_Implementation();

	//Metoda inicjalizujaca siatke broni
	UFUNCTION(Server, Reliable, WithValidation)
		void Init();
	bool Init_Validate() { return true; };
	void Init_Implementation();

	// Śmierć postaci
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void KillPlayer();
		bool KillPlayer_Validate() { return true; };
		void KillPlayer_Implementation();
	
	// Ożywienie postaci
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void RespawnPlayer();
		bool RespawnPlayer_Validate() { return true; };
		void RespawnPlayer_Implementation();
	
	// Reset siatki
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void ResetMesh();
		bool ResetMesh_Validate() { return true; };
		void ResetMesh_Implementation();

	// Metoda strzalu postaci
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void Fire();
		bool Fire_Validate() { return true; };
		void Fire_Implementation();

	// Metoda strzalu postaci
	//UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	UFUNCTION(BlueprintCallable, Category = "GCharacter")
	void Throw(class AGProjectile * ProjectileClass, FVector Offset);
		//bool Throw_Validate(class AGProjectile * ProjectileClass) { if (ProjectileClass) return true; else return false; };
		//void Throw_Implementation(class AGProjectile * ProjectileClass);

	//Zadaj obrażenia
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void InflictDamage( float DamageAmount , const FHitResult& Hit );
		bool InflictDamage_Validate( float DamageAmount, const FHitResult& Hit ) { return true; };
		void InflictDamage_Implementation( float DamageAmount, const FHitResult& Hit );

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
	void SetSkillA(bool nSkillA);
		bool SetSkillA_Validate(bool nSkillA) { return true; };
		void SetSkillA_Implementation(bool nSkillA);

	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
		void SetSkillB(bool nSkillB);
	bool SetSkillB_Validate(bool nSkillA) { return true; };
	void SetSkillB_Implementation(bool nSkillB);
	
	UFUNCTION(Server, Reliable, WithValidation, BlueprintCallable, Category = "GCharacter")
		void SetSkillC(bool nSkillC);
	bool SetSkillC_Validate(bool nSkillC) { return true; };
	void SetSkillC_Implementation(bool nSkillC);

	//Metoda do oslugi replikacji [silnik]
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty > & OutLifetimeProps) const;

/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/// Zmienne
/// /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
	private:

	// Czy zainicjowano 
	UPROPERTY()
		bool Inited;

	// Punkty zdrowia
	UPROPERTY(Replicated)
		float Health;

	//Wynik gracza //TODO:: pzrenies do PlayerState
	UPROPERTY(Replicated)
		int Score;

	//Uchwyt do timera odrodzajacego gracza
	UPROPERTY()
		FTimerHandle RespawnTimerHandle;

	// Uchwyt na bron widziana w pierwszej osobie
	UPROPERTY(Replicated)
		AGWeaponBase * FPSWeapon;

	// Uchwyt na broń
	UPROPERTY(Replicated)
		AGWeaponBase * Weapon;

	// Czy postac strzela
	UPROPERTY(Replicated)
		bool IsFiring;

	// Czy postac przeładowuje broń
	UPROPERTY(Replicated)
		bool IsReloading;

	// Czy postac puzywa umiejetności A
	UPROPERTY(Replicated)
		bool IsUsingSkillA;

	// Czy postac puzywa umiejetności B
	UPROPERTY(Replicated)
		bool IsUsingSkillB;

	// Czy postac puzywa umiejetności C
	UPROPERTY(Replicated)
		bool IsUsingSkillC;

	//
	UPROPERTY(Replicated)
		int IndexWeapon;

	public:

	// Zmienna opuźniajaca wystrzaly
	UPROPERTY(Replicated)
		float FireDelay;

	// Zmienna opuźniajaca wystrzaly
	UPROPERTY(Replicated)
		float SkillADelay;

	// Zmienna opuźniajaca wystrzaly
	UPROPERTY(Replicated)
		float SkillBDelay;

	// Zmienna opuźniajaca wystrzaly
	UPROPERTY(Replicated)
		float SkillCDelay;

	// FPS camera.
	UPROPERTY(VisibleAnywhere)
		UCameraComponent * FPSCameraComponent;

	// Siatka widziana przez kamere
	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent * ArmsMeshComponent;

	// Klasa broni - wybor w silniku
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
		TSubclassOf<class AGWeaponBase> WeaponClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon, Replicated)
		TArray<TSubclassOf<class AGWeaponBase>> WeaponBackpack;
};
