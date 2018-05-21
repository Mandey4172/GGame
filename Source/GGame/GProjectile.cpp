// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GProjectile.h"
#include "GCharacter.h"
#include "UnrealNetwork.h"

/* Konstruktor. */
AGProjectile::AGProjectile()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	// Uzywaj kuli do reprezentacji kolizji
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AGProjectile::OnHit);
	// Promien kuli
	CollisionComponent->InitSphereRadius(1.0f);
	// Ustawianie glownego komponentu jako component kuli
	RootComponent = CollisionComponent;
	// Uzywaj komponentu poruszania sie pocisku do opisu ruchu pocisku
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->SetUpdatedComponent(CollisionComponent);
	ProjectileMovementComponent->InitialSpeed = 3000.0f;
	ProjectileMovementComponent->MaxSpeed = 3000.0f;
	ProjectileMovementComponent->bRotationFollowsVelocity = true;
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->Bounciness = 0.3f;
	ProjectileMovementComponent->ProjectileGravityScale = 1.0f;
	// Uwanie komponentu statycznej siatki do opisu wygladu pocisu
	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->AttachTo(CollisionComponent);
	// Zniszcz po 
	InitialLifeSpan = 10.0f;
	//
	Damage = 10;
}

/* Metoda wywowylaca podczas dodania postaci do gry. */
void AGProjectile::BeginPlay()
{
	Super::BeginPlay();
}

/* Metoda wywowylana co klatke. */
void AGProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* Metoda przygotowujaca pocisk do wystrzalu */
void AGProjectile::FireInDirection(const FVector& ShootDirection)
{
	//Ustaw przemieszczenie
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

/* Metoda wywowylana podczas uderzenia */
void AGProjectile::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OtherActor != this)
	{
		//Sprawdzanie czy Actor to nasza postac [Rzutowanie actora na AGCharacter i sprawdzenie czy zrzutowany obiek nie jest null]
		AGCharacter * HitCharacter = Cast<AGCharacter>(OtherActor);
		if (HitCharacter  && HitCharacter != ProjectileOwner)
		{
			//Zadanie obrazen
			HitCharacter->InflictDamage(this->Damage, Hit);
			if (ProjectileOwner && (HitCharacter->GetHealth() <= 0))
			{
				ProjectileOwner->ScorePoint();
			}
		}
		SetLifeSpan(0.000001f);
	}
}

/* Ustaw w³aœcicela pocisku */
void AGProjectile::SetProjectileOwner(AGCharacter * nProjectileOwner)
{
	ProjectileOwner = nProjectileOwner;
}

/* Pobierz w³aœcicela */
AGCharacter * AGProjectile::GetProjectileOwner()
{
	return ProjectileOwner;
}

/* Metoda potrzebna do replikacji */
void AGProjectile::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGProjectile, ProjectileOwner);
}