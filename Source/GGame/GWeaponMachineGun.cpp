// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GWeaponMachineGun.h"
#include "GBullet.h"
#include "UnrealNetwork.h"

// Konstruktor.
	//Ustawia pewne domyslne wartosci.
AGWeaponMachineGun::AGWeaponMachineGun()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = false;

	// Opuznienie 
	Delay = 0.075f;
	// Przeladowanie
	ReloadDelay = 2.0f;
	// Rozrzut (aktualny)
	Recoil = 0.0f;
	// Maksymalny rozrzut 
	MaximalRecoil = 2.5f;
	// Minimalny rozrzut 
	MinimalRecoil = 0.05f;
	// Czas do osiagniecia maksymalnego rozrzutu
	MaxRecoilTime = 0.6f;
	// Czas do ustabilizowania rozrzutu
	MinRecoilTime = 2.0f;
	// Pojemnosc magazynku
	MagazineSize = 24;
	// Aktualna ilosc naboji
	InMagazine = 0;
	// Obra¿enia
	Damage = 2.f;
	// Replikacja po sieci
	bReplicates = true;
}
// Metoda wywowylaca podczas dodania postaci do gry.
void AGWeaponMachineGun::BeginPlay()
{
	Super::BeginPlay();
	// Aktualna ilosc naboji
	InMagazine = MagazineSize;
}

void AGWeaponMachineGun::Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WeaponA:: Shoot()"));
	if (this->ProjectileClass)
	{
		float tangle = FMath::FRandRange(0, 359),
			tpitch = FMath::Cos(tangle),
			tyaw = FMath::Sin(tangle);
		//Wyliczenie pozycji utworzenie pocisku
		PLocation = PLocation + FTransform(PRotation).TransformVector(MuzzleOffset);
		// Lekko podnosimy strzal.
		PRotation.Pitch += FMath::FRandRange(0, this->GetRecoil()) * tpitch;
		PRotation.Yaw += FMath::FRandRange(0, this->GetRecoil()) * tyaw;
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			// Tworzy pocisk w grze.
			AGBullet* Projectile = World->SpawnActor<AGBullet>(ProjectileClass, PLocation, PRotation, SpawnParams);
			Projectile->SetProjectileOwner(ProjectileOwner);
			if (Projectile)
			{
				// Ustawianie trajektori pocisku
				FVector LaunchDirection = PRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
				InMagazine--;
				if (this->GetRecoil() < this->GetMaximalRecoil())
					Recoil += this->GetDelay() * ((this->GetMaximalRecoil() - this->GetMinimalRecoil()) / this->GetTimeToReachMaximalRecoil());
				else if (this->GetRecoil() > this->GetMaximalRecoil())
					Recoil = this->GetMaximalRecoil();
			}
		}
	}
}

float AGWeaponMachineGun::GetRecoil()
{
	return Recoil;
}

float AGWeaponMachineGun::GetMaximalRecoil()
{
	return MaximalRecoil;
}

float AGWeaponMachineGun::GetMinimalRecoil()
{
	return MinimalRecoil;
}

float AGWeaponMachineGun::GetTimeToReachMaximalRecoil()
{
	return MaxRecoilTime;
}

float AGWeaponMachineGun::GetTimeToReachMinimalRecoil()
{
	return MinRecoilTime;
}

void AGWeaponMachineGun::UpdateRecoil(float DeltaTime)
{
	if( this->GetRecoil() > this->GetMinimalRecoil() )
		Recoil -= DeltaTime * this->GetDelay() * ( (this->GetMaximalRecoil() - this->GetMinimalRecoil()) / this->GetTimeToReachMinimalRecoil() );
	if( this->GetRecoil() < this->GetMinimalRecoil() )
		Recoil = this->GetMinimalRecoil();
}

void AGWeaponMachineGun::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGWeaponMachineGun, MagazineSize);
    DOREPLIFETIME(AGWeaponMachineGun, InMagazine);
	DOREPLIFETIME(AGWeaponMachineGun, Recoil);
}

