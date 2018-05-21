// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GBullet.h"
#include "GCharacter.h"
#include "UnrealNetwork.h"

/* Konstruktor. */
AGBullet::AGBullet()
{
 	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	// Uzywaj kuli do reprezentacji kolizji
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Projectile"));
	CollisionComponent->OnComponentHit.AddDynamic(this, &AGBullet::OnHit);
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
	ProjectileMovementComponent->Bounciness = 0.0f;
	ProjectileMovementComponent->ProjectileGravityScale = 0.0f;
	// Uwanie komponentu statycznej siatki do opisu wygladu pocisu
	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->AttachTo(CollisionComponent);
	// Zniszcz po 
	InitialLifeSpan = 10.0f;
}

/* Metoda wywowylaca podczas dodania postaci do gry. */
void AGBullet::BeginPlay()
{
	Super::BeginPlay();
} 

/* Metoda wywowylana co klatke. */
void AGBullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

/* Metoda przygotowujaca pocisk do wystrzalu */
void AGBullet::FireInDirection(const FVector& ShootDirection)
{
	//Ustaw przemieszczenie
	ProjectileMovementComponent->Velocity = ShootDirection * ProjectileMovementComponent->InitialSpeed;
}

/* Metoda wywowylana podczas uderzenia */
void AGBullet::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if ( OtherActor != this )
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GBullet ONHIT"));
		//Sprawdzanie czy Actor to nasza postac [Rzutowanie actora na AGCharacter i sprawdzenie czy zrzutowany obiek nie jest null]
		AGCharacter * HitCharacter = Cast<AGCharacter>(OtherActor);
		if(HitCharacter)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GBullet HitCharacter exist"));
			//Zadanie obrazen
			HitCharacter->InflictDamage(this->ProjectileOwner->GetWeapon()->GetDamage(), Hit);
			if(ProjectileOwner && (HitCharacter->GetHealth() <= 0) )
			{
				ProjectileOwner->ScorePoint();
			}
		}
	}
	SetLifeSpan(0.000001f);
}

/* Ustaw wlascicela pocisku */
void AGBullet::SetProjectileOwner(AGCharacter * nProjectileOwner)
{
	ProjectileOwner = nProjectileOwner;
}

/* Pobierz wlascicela */
AGCharacter * AGBullet::GetProjectileOwner()
{
	return ProjectileOwner;
}

/* Metoda potrzebna do replikacji */
void AGBullet::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGBullet, ProjectileOwner);
}