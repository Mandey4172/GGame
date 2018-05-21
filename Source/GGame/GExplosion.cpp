// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GExplosion.h"
#include "GCharacter.h"
#include "UnrealNetwork.h"


// Sets default values
AGExplosion::AGExplosion()
{
	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	// Uzywaj kuli do reprezentacji kolizji
	CollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("SphereComponent"));
	CollisionComponent->BodyInstance.SetCollisionProfileName(TEXT("Explosion"));
	CollisionComponent->bGenerateOverlapEvents = true;

	// Promien kuli
	CollisionComponent->InitSphereRadius(1.0f);
	// Ustawianie glownego komponentu jako component kuli
	RootComponent = CollisionComponent;

	// Uwanie komponentu statycznej siatki do opisu wygladu pocisu
	ActorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComponent"));
	ActorMeshComponent->AttachTo(CollisionComponent);
	// Zniszcz po 
	//InitialLifeSpan = 10.0f;

	Damage = 10.f;

	ChangeOfRadius = 10.f;

	
}

// Called when the game starts or when spawned
void AGExplosion::BeginPlay()
{
	Super::BeginPlay();
	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AGExplosion::OnOverlapBegin);
}

// Called every frame
void AGExplosion::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	float Radius = this->CollisionComponent->GetUnscaledSphereRadius();
	if(Radius > MaximalRadius) 
		SetLifeSpan(0.000001f);
	Radius += DeltaTime * ChangeOfRadius;
	this->CollisionComponent->SetSphereRadius(Radius);
}

void AGExplosion::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("GExplosion OverLeapBegin"));
	if (OtherActor != this)
	{
		//Sprawdzanie czy Actor to nasza postac [Rzutowanie actora na AGCharacter i sprawdzenie czy zrzutowany obiek nie jest null]
		AGCharacter * HitCharacter = Cast<AGCharacter>(OtherActor);
		if (HitCharacter)
		{
			FHitResult Hit;
			//Zadanie obrazen
			HitCharacter->InflictDamage(this->Damage,Hit);
			if (ExplosionOwner && (HitCharacter->GetHealth() <= 0))
			{
				ExplosionOwner->ScorePoint();
			}
		}
	}
}

void AGExplosion::SetExplosionOwner(AGCharacter * NExplosionOwner)
{
	ExplosionOwner = NExplosionOwner;
}

AGCharacter * AGExplosion::GetExplosionOwner()
{
	return ExplosionOwner;
}

void AGExplosion::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGExplosion, ExplosionOwner);
}
