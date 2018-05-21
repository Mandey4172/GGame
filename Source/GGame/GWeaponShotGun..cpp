// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GWeaponShotGun.h"
#include "GBullet.h"

AGWeaponShotGun::AGWeaponShotGun()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = false;
	// Opuznienie 
	Delay = 1.0f;
	// Przeladowanie
	ReloadDelay = 10.0f;
	//
	Recoil = 0;
	//
	MaximalRecoil = 2.5f;
	//
	MinimalRecoil = 1.0f;
	//
	MaxRecoilTime = 0.6f;
	//
	MinRecoilTime = 2.0f;
	// Pojemnosc magazynku
	MagazineSize = 20;
	// Aktualna ilosc naboji
	InMagazine = 0;
	//
	Damage = 10.f;
    //
    ProjectilesPerShoot = 6;
	// Replikacja po sieci
	bReplicates = true;
}

/* Strzal broni */
void AGWeaponShotGun::Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("WeaponA:: Shoot()"));
	if (this->ProjectileClass)
	{
        PLocation = PLocation + FTransform(PRotation).TransformVector(MuzzleOffset);
        TArray<FRotator> TPRotation;
        for(int i = 0; i < GetProjectilesPerShoot(); i++)
        {
            float tangle = FMath::FRandRange(0, 359),
			tpitch = FMath::Cos(tangle),
			tyaw = FMath::Sin(tangle);
            //Wyliczenie pozycji utworzenie pocisku
            TPRotation.Add(PRotation);
            // Lekko podnosimy strzal.
            TPRotation[i].Pitch += FMath::FRandRange(0, this->GetRecoil()) * tpitch;
            TPRotation[i].Yaw += FMath::FRandRange(0, this->GetRecoil()) * tyaw;
        }
		if (World)
		{
            for(FRotator& ARotation : TPRotation)
            {
                FActorSpawnParameters SpawnParams;
                // Tworzy pocisk w grze.
                AGBullet* Projectile = World->SpawnActor<AGBullet>(ProjectileClass, PLocation, ARotation, SpawnParams);
                Projectile->SetProjectileOwner(ProjectileOwner);
                if (Projectile)
                {
                    // Ustawianie trajektori pocisku
                    FVector LaunchDirection = ARotation.Vector();
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
}

/* Ustaw iloœæ kul na wystrzal*/
void AGWeaponShotGun::SetProjectilesPerShoot( int NProjectilesPerShoot )
{
    this->ProjectilesPerShoot = NProjectilesPerShoot;
}

/* Pobierz iloœæ kul na wystrzal */
int AGWeaponShotGun::GetProjectilesPerShoot()
{
    return this->ProjectilesPerShoot;
}