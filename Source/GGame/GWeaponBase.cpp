// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GWeaponMachineGun.h"
#include "GBullet.h"
#include "UnrealNetwork.h"

/* Konstruktor. */
AGWeaponBase::AGWeaponBase()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = false;
	// Tworzenie komponentu kuli z kolizja
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	// Ustawianie promienia kuli
	CollisionComponent->InitSphereRadius(1.0f);
	// Ustanienie glownego komponentu jako komponentu kuli
	RootComponent = CollisionComponent;
	// Komponent siatki
	MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	// Prztwierdzenie do glownego komponentu
	MeshComponent->AttachTo(GetRootComponent());
	// Opuznienie 
	Delay = 1.0f;
	// Przeladowanie
	ReloadDelay = 10.0f;
	// Pojemnosc magazynku
	MagazineSize = 20;
	// Aktualna ilosc naboji
	InMagazine = 0;
	// Obra¿enia
	Damage = 10.f;
	// Replikacja po sieci
	bReplicates = true;

}

// Metoda wywowylaca podczas dodania postaci do gry.
void AGWeaponBase::BeginPlay()
{
	Super::BeginPlay();
	// Aktualna ilosc naboji
	InMagazine = MagazineSize;
}

/* Strzal broni */
void AGWeaponBase::Shoot(FVector PLocation, FRotator PRotation, UWorld * World, AGCharacter * ProjectileOwner)
{
	if (this->ProjectileClass)
	{
		float tangle = FMath::FRandRange(0, 359),
			tpitch = FMath::Cos(tangle),
			tyaw = FMath::Sin(tangle);
		//Wyliczenie pozycji utworzenie pocisku
		PLocation = PLocation + FTransform(PRotation).TransformVector(MuzzleOffset);
		// Lekko podnosimy strzal.
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
			}
		}
	}
}

/* Pobierz czas do nastepnego wystrza³u */
float AGWeaponBase::GetDelay()
{
	return Delay;
}

/* Prze³aduj broñ (zwraca czas prze³adowania ) */
float AGWeaponBase::Reload()
{
	InMagazine = MagazineSize;
	MeshComponent->SetRelativeRotation(FRotator(0.f,300.f,0.f));
	return ReloadDelay;
}

/* Pobiera pojemnoœæ magazynku */
int AGWeaponBase::GetMagazineSize()
{
	return MagazineSize;
}

/* Pobiera ile kul jest w magazynku */
int AGWeaponBase::GetBulletsInMaggazie()
{
	return InMagazine;
}

int AGWeaponBase::GetDamage()
{
	return Damage;
}

/* Pobierz obra¿enia kuli*/
void AGWeaponBase::UpdateRecoil(float DeltaTime)
{

}

void AGWeaponBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGWeaponBase, MagazineSize);
	DOREPLIFETIME(AGWeaponBase, InMagazine);
}


