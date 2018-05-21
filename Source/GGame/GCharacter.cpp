// Fill out your copyright notice in the Description page of Project Settings.

#include "GGame.h"
#include "GCharacter.h"
#include "GWeaponBase.h"
#include "GProjectile.h"
#include "GPlayerState.h"
#include "GGamePlayerController.h"
#include "GGameInstance.h"
#include "UnrealNetwork.h"

/* Konstruktor. */
AGCharacter::AGCharacter()
{
 	// Czy character ma wywowylac metode Tick()
	PrimaryActorTick.bCanEverTick = true;
	
	
	//this->BodyInstance.SetCollisionProfileName(TEXT("Character"));

	this->GetCapsuleComponent()->bGenerateOverlapEvents = true;
	// Tworzenie komponentu kamery w postaci
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("First Person Camera"));
	// Prztwierdzenie do glownego komponentu
	FPSCameraComponent->AttachTo(GetCapsuleComponent());
	// Ustawienie pozycji kamery nieco powyzej oczu.
	FPSCameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));
	// Pozwala na kontrole rotacji postaci
	FPSCameraComponent->bUsePawnControlRotation = true;

	// Tworzenie komponentu siatki dla wlasciciela postaci
	ArmsMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("First Person Mesh"));
	// Tylko wlasciciel widzi siatke
	ArmsMeshComponent->SetOnlyOwnerSee(true);
	// Prztwierdzenie do komponentu kamery
	ArmsMeshComponent->AttachTo(FPSCameraComponent);
	// Wylaczenie cieniowanie w celu pominiecia podwujnego cienia. 
	ArmsMeshComponent->bCastDynamicShadow = false;
	ArmsMeshComponent->CastShadow = false;
	// Wylaczenie zwyklej siatki dla wlasciciela
	GetMesh()->SetOwnerNoSee(true);
	//Ods
	FireDelay = 0;

	SkillADelay = 0;
	SkillBDelay = 0;
	SkillCDelay = 0;

	Health = 100;
	Score = 0;
	//Flagi
	IsFiring = false;
	Inited = true;

	IndexWeapon = 0;

	// Replikacja po sieci
	bReplicates = true;
}

/* Metoda wywowylaca podczas dodania postaci do gry. */
void AGCharacter::BeginPlay()
{
	Super::BeginPlay();
	//Pobieranie domyslnego swiata
	/*if(HasAuthority())
	{
		
	}*/
	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry dodawania postaci do gry
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//Dodanie broni do gry
		if (!Weapon && this->WeaponBackpack[IndexWeapon])
		{
			//Weapon = World->SpawnActor<AGWeaponBase>(WeaponClass, SpawnParams);
			Weapon = World->SpawnActor<AGWeaponBase>(this->WeaponBackpack[IndexWeapon], SpawnParams);
		}
		if (!FPSWeapon && this->WeaponBackpack[IndexWeapon])
		{
			//FPSWeapon = World->SpawnActor<AGWeaponBase>(WeaponClass, SpawnParams);		
			FPSWeapon = World->SpawnActor<AGWeaponBase>(this->WeaponBackpack[IndexWeapon], SpawnParams);
		}
		if (Weapon)
		{
			//Przytwierdzenie do postaci
			Weapon->AttachRootComponentTo(GetMesh(), TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
			Weapon->MeshComponent->SetOwnerNoSee(true);
		}
		if (FPSWeapon)
		{
			FPSWeapon->MeshComponent->AttachTo(ArmsMeshComponent, TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
			FPSWeapon->MeshComponent->SetOnlyOwnerSee(true);
			FPSWeapon->MeshComponent->bCastDynamicShadow = false;
			FPSWeapon->MeshComponent->CastShadow = false;
		}
	}
}

/* Metoda wywowylaca podczas konca gry.*/
void AGCharacter::EndPlay(const EEndPlayReason::Type EndPlayReason) 
{
	Super::EndPlay(EndPlayReason);
	//Zabijanie broni
	if(this->Weapon)
		this->Weapon->SetLifeSpan(0.001f);
	if (this->FPSWeapon)
		this->FPSWeapon->SetLifeSpan(0.001f);
}

/* Metoda wywowylana co klatke. */
void AGCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//TODO :: Zmien na TimedEvent odpalany w construktorze (test)
	//Inicjacja
	/*if (Inited)
	{
		Init();
	}*/
	//Aktualizuj licznik do nastepnego wystrzalu
	if (FireDelay > 0)
	{
		FireDelay -= DeltaTime;
		if (FireDelay < 0)
		{
			FireDelay = 0;
		}//MeshComponent->SetRelativeLocation(FVector(0.f, 0.f, -20.f));	
		if (FireDelay == 0)
		{
			this->FPSWeapon->MeshComponent->SetRelativeRotation(FRotator(0.f,0.f,0.f));
		}
	}
	if (SkillADelay > 0)
		SkillADelay -= DeltaTime;
	if (SkillBDelay > 0)
		SkillBDelay -= DeltaTime;
	if (SkillCDelay > 0)
		SkillCDelay -= DeltaTime;
	//Czy postac strzela
	if (IsFiring)
	{
		Fire_Implementation();
		if (Role < ROLE_Authority)
		{
			Fire();
		}
	}
	//Aktualizuj rozrzutu broni
	if (this->GetWeapon())
	{
		this->GetWeapon()->UpdateRecoil(DeltaTime);
	}
}

/* Funkcja ustawiajaca input. */
void AGCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// Ustawianie wiazan "movement".
	InputComponent->BindAxis("MoveForward", this, &AGCharacter::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AGCharacter::MoveRight);
	// Ustawianie wiazan "look".
	InputComponent->BindAxis("Turn", this, &AGCharacter::AddControllerYawInput);
	InputComponent->BindAxis("LookUp", this, &AGCharacter::AddControllerPitchInput);
	//
	InputComponent->BindAction("MouseWheelUp", IE_Pressed, this, &AGCharacter::MouseWheelUp);
	InputComponent->BindAction("MouseWheelDown", IE_Pressed, this, &AGCharacter::MouseWheelDown);
	// Ustawianie wiazan "action".
	InputComponent->BindAction("Jump", IE_Pressed, this, &AGCharacter::StartJump);
	InputComponent->BindAction("Jump", IE_Released, this, &AGCharacter::StopJump);
	// Ustawianie wiazan "fire".
	InputComponent->BindAction("Fire", IE_Pressed, this, &AGCharacter::FireStart);
	InputComponent->BindAction("Fire", IE_Released, this, &AGCharacter::FireStop);
	// Ustawianie wiazan "reload".
	InputComponent->BindAction("Reload", IE_Pressed, this, &AGCharacter::StartReload);
	InputComponent->BindAction("Reload", IE_Released, this, &AGCharacter::StopReload);
	// Ustawianie wiazan "skillA".
	InputComponent->BindAction("SkillA", IE_Pressed, this, &AGCharacter::StartSkillA);
	InputComponent->BindAction("SkillA", IE_Released, this, &AGCharacter::StopSkillA);
	// Ustawianie wiazan "skillB".
	InputComponent->BindAction("SkillB", IE_Pressed, this, &AGCharacter::StartSkillB);
	InputComponent->BindAction("SkillB", IE_Released, this, &AGCharacter::StopSkillB);
	// Ustawianie wiazan "skillC".
	InputComponent->BindAction("SkillC", IE_Pressed, this, &AGCharacter::StartSkillC);
	InputComponent->BindAction("SkillC", IE_Released, this, &AGCharacter::StopSkillC);
}

/* smierc postaci */
void AGCharacter::KillPlayer_Implementation()
{
	TeleportTo(FVector(0.0f, 0.0f, -1000.0f), FRotator(0.f), true, true);
	DisableInput(NULL);
	SetActorHiddenInGame(true);
	SetActorTickEnabled(false);

	if (Weapon)
	{
		Weapon->SetActorHiddenInGame(true);
	}
	if (this->FPSWeapon)
	{
		FPSWeapon->SetActorHiddenInGame(true);
	}
}

/*Ozywienie postaci*/
void AGCharacter::RespawnPlayer_Implementation()
{
	//Wyszukiwanie wszystkich punktow startowych
	TArray<AActor*> ActorStartPoints;
 	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), ActorStartPoints);
	//Losowanie punktu startowego
	int i = FMath::RandRange( 0,ActorStartPoints.Num() - 1);
	//Przemieszczenie martwej postaci do punktu startowego
	TeleportTo(ActorStartPoints[i]->GetActorLocation(),FRotator(0.f));
	APlayerController * PController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	//Reset zdrowia
	Health = 100;
	//Czyszczenie licznika wywo³ujacego ta metode 
	GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);
	//Przywrocenie kontroli nad postacia graczowi
	if (PController)
	{
		EnableInput(PController);
	}
	//Resetowanie siatek
	ResetMesh();
}

/*Reset siatki*/
void AGCharacter::ResetMesh_Implementation()
{
	
	SetActorHiddenInGame(false);
	SetActorTickEnabled(true);
	if(Weapon)
	{
		Weapon->SetActorHiddenInGame(false);
	}
	if(this->FPSWeapon)
	{
		FPSWeapon->SetActorHiddenInGame(false);
	}
	if (Weapon)
	{
		//Przytwierdzenie do postaci
		Weapon->AttachRootComponentTo(GetMesh(), TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
		Weapon->MeshComponent->SetOwnerNoSee(true);
	}
	if(FPSWeapon)
	{
		FPSWeapon->MeshComponent->AttachTo(ArmsMeshComponent, TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
		FPSWeapon->MeshComponent->SetOnlyOwnerSee(true);
		FPSWeapon->MeshComponent->bCastDynamicShadow = false;
		FPSWeapon->MeshComponent->CastShadow = false;
	}
}

/* Metoda strzalu postaci */
void AGCharacter::Fire_Implementation()
{
	if (WeaponClass && IsFiring && FireDelay <= 0)
	{
		FVector MuzzleLocation;
		FRotator MuzzleRotation;
		//Pobieranie pozycji kamery
		GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);
		if (GetWeapon())
		{
			if (GetWeapon()->GetBulletsInMaggazie() > 0)
			{
				GetWeapon()->Shoot(MuzzleLocation, MuzzleRotation, GetWorld(), this);
				FireDelay = GetWeapon()->GetDelay();
			}
			else
			{
				FireDelay = GetWeapon()->Reload();
			}
		}
	}
}

void AGCharacter::Throw(AGProjectile * ProjectileClass, FVector Offset)
{
	if (ProjectileClass)
	{
		FVector MuzzleLocation;
		FRotator MuzzleRotation;
		//Pobieranie pozycji kamery
		GetActorEyesViewPoint(MuzzleLocation, MuzzleRotation);
		//Wyliczenie pozycji utworzenie pocisku
		MuzzleLocation = MuzzleLocation + FTransform(MuzzleRotation).TransformVector(Offset);
		// Lekko podnosimy strzal.
		if (GetWorld())
		{
			FActorSpawnParameters SpawnParams;
			// Tworzy pocisk w grze.
			AGProjectile* Projectile = GetWorld()->SpawnActor<AGProjectile>(ProjectileClass->GetClass(), MuzzleLocation, MuzzleRotation, SpawnParams);
			Projectile->SetProjectileOwner(this);
			if (Projectile)
			{
				// Ustawianie trajektori pocisku
				FVector LaunchDirection = MuzzleRotation.Vector();
				Projectile->FireInDirection(LaunchDirection);
			}
		}
	}
}

/* Rozpoczecie strzelania */
void AGCharacter::FireStart_Implementation()
{
	IsFiring = true;
}

/* Zakonczenie strzelania */
void AGCharacter::FireStop_Implementation()
{
	IsFiring = false;
}

/* Zadaj obrazenia */
void AGCharacter::InflictDamage_Implementation(float DamageAmount, const FHitResult& Hit)
{
	APlayerController* PlayerController = Cast<APlayerController>(GetController());
	TSubclassOf<UDamageType> const ValidDamageTypeClass = TSubclassOf<UDamageType>(UDamageType::StaticClass());
	FDamageEvent DamageEvent(ValidDamageTypeClass);
	this->TakeDamage(DamageAmount, DamageEvent, PlayerController, this);
	//IsFiring = true;
}

/* Metoda obslugujaca zadawanie obrazen postaci */
float AGCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GCharacter Take Damage :: %f"), DamageAmount ));
	const float ActualDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (ActualDamage > 0.f)
	{
		Health -= ActualDamage;
		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
		if (Health <= 0.f)
		{
			KillPlayer();
			if (GetWorld() && !RespawnTimerHandle.IsValid())
			{
				GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AGCharacter::RespawnPlayer, 10.0f, false);
			}
		}
	}
	return ActualDamage;
}

//float AGCharacter::ReceiveAnyDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("GCharacter Recive Any Damage :: %f"), DamageAmount));
//	const float ActualDamage = DamageAmount;//Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
//	if (ActualDamage > 0.f)
//	{
//		Health -= ActualDamage;
//		// If the damage depletes our health set our lifespan to zero - which will destroy the actor  
//		if (Health <= 0.f)
//		{
//			KillPlayer();
//			if (GetWorld() && !RespawnTimerHandle.IsValid())
//			{
//				GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AGCharacter::RespawnPlayer, 10.0f, false);
//			}
//		}
//	}
//	return ActualDamage;
//}

/* Metoda poruszajaca postac przod - tyl. */
void AGCharacter::MoveForward(float Value)
{
	//Znajdywanie odpowiedniego przesuniecia do przodu w oparciu o pozycje i rotacje.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

/* Metoda poruszajaca postac prawo. */
void AGCharacter::MoveRight(float Value)
{
	//Znajdywanie odpowiedniego przesuniecia w prawo w oparciu o pozycje i rotacje.
	FVector Direction = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

/*  */
void AGCharacter::MouseWheelUp()
{
	SwapWeapon(1);
}

/*  */
void AGCharacter::MouseWheelDown()
{
	SwapWeapon(-1);
}

/* Metoda ustawiajaca flage skoku. */
void AGCharacter::StartJump()
{
	bPressedJump = true;
}

/* Metoda czyszczaca flage skoku. */
void AGCharacter::StopJump()
{
	bPressedJump = false;
}

/* Metoda ustawiajaca flage . */
void AGCharacter::StartReload()
{
	IsReloading = true;
}

/* Metoda czyszczaca flage . */
void AGCharacter::StopReload()
{
}

/* Metoda ustawiajaca flage . */
void AGCharacter::StartSkillA()
{
	IsUsingSkillA = true;
	this->GetCharacterMovement()->MaxWalkSpeed = 2000;

	if (Role < ROLE_Authority)
	{
		SetSkillA(true);
	}
}

/* Metoda czyszczaca flage . */
void AGCharacter::StopSkillA()
{
	IsUsingSkillA = false;
	this->GetCharacterMovement()->MaxWalkSpeed = 600;

	if (Role < ROLE_Authority)
	{
		SetSkillA(false);
	}
}

/* Metoda ustawiajaca flage . */
void AGCharacter::StartSkillB()
{
	IsUsingSkillB = true;
	if (Role < ROLE_Authority)
	{
		SetSkillB(true);
	}
}

/* Metoda czyszczaca flage . */
void AGCharacter::StopSkillB()
{
	IsUsingSkillB = false;
	if (Role < ROLE_Authority)
	{
		SetSkillB(false);
	}
}

/* Metoda ustawiajaca flage . */
void AGCharacter::StartSkillC()
{
	IsUsingSkillC = true;
	if (Role < ROLE_Authority)
	{
		SetSkillC(true);
	}
}

/* Metoda czyszczaca flage . */
void AGCharacter::StopSkillC()
{
	IsUsingSkillC = false;
	if (Role < ROLE_Authority)
	{
		SetSkillC(false);
	}
}
/* Metoda strzalu postaci */
void AGCharacter::Init_Implementation()
{
	/*
	UGameInstance * TGameInstance = GetGameInstance();
	if (TGameInstance)
	{
		//TODO przenies
		UGGameInstance * TGGameInstance = Cast<UGGameInstance>(TGameInstance);
		if (TGGameInstance)
		{
			AGPlayerState * PlayerState = Cast<AGPlayerState>(GetWorld()->GetFirstPlayerController()->PlayerState);
			PlayerState->SetSaveGame(TGGameInstance->LoadCharacterSave());

			//CharacterSaveGame = TGGameInstance->LoadCharacterSave();
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString(TEXT("Character Saved Loaded")));
		}
	}
	*/
	Inited = false;
	if (Weapon && FPSWeapon)
	{
		//Przytwierdzenie siatki broni do postaci widzianej z 3 osoby
		Weapon->AttachRootComponentTo(GetMesh(), TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
		Weapon->MeshComponent->SetOwnerNoSee(true);
		//Przytwierdzenie siatki broni do postaci widzianej z 1 osoby
		FPSWeapon->AttachRootComponentToActor(this);
		FPSWeapon->MeshComponent->AttachTo(ArmsMeshComponent, TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
		FPSWeapon->MeshComponent->SetOnlyOwnerSee(true);
		FPSWeapon->MeshComponent->bCastDynamicShadow = false;
		FPSWeapon->MeshComponent->CastShadow = false;
	}
	else
		Inited = true;
}

/**/ 
void AGCharacter::SwapWeapon_Implementation(float Value)
{
	if (Value == 0.0f) return;
	else if (Value > 0.0f) IndexWeapon++;
	else IndexWeapon--;
	if (IndexWeapon >= this->WeaponBackpack.Num())
	{
		IndexWeapon = 0;
	}

	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("Weapon Num: %f"), IndexWeapon));// TEXT("Weapon Num: "));
	this->Weapon->SetLifeSpan(0.001f);
	this->FPSWeapon->SetLifeSpan(0.001f);

	UWorld* World = GetWorld();
	if (World)
	{
		//Parametry dodawania postaci do gry
		FActorSpawnParameters SpawnParams;
		SpawnParams.Owner = this;
		//Dodanie broni do gry
		if (this->WeaponBackpack[IndexWeapon])
		{
			//Weapon = World->SpawnActor<AGWeaponBase>(WeaponClass, SpawnParams);
			Weapon = World->SpawnActor<AGWeaponBase>(this->WeaponBackpack[IndexWeapon], SpawnParams);
		}
		if (this->WeaponBackpack[IndexWeapon])
		{
			//FPSWeapon = World->SpawnActor<AGWeaponBase>(WeaponClass, SpawnParams);		
			FPSWeapon = World->SpawnActor<AGWeaponBase>(this->WeaponBackpack[IndexWeapon], SpawnParams);
		}
		if (Weapon)
		{
			//Przytwierdzenie do postaci
			Weapon->AttachRootComponentTo(GetMesh(), TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
			Weapon->MeshComponent->SetOwnerNoSee(true);
		}
		if (FPSWeapon)
		{
			FPSWeapon->MeshComponent->AttachTo(ArmsMeshComponent, TEXT("WeaponSocket"), EAttachLocation::SnapToTarget, true);
			FPSWeapon->MeshComponent->SetOnlyOwnerSee(true);
			FPSWeapon->MeshComponent->bCastDynamicShadow = false;
			FPSWeapon->MeshComponent->CastShadow = false;
		}
	}
}

/* Metoda pobierajaca bron postaci */
AGWeaponBase * AGCharacter::GetWeapon()
{
	return FPSWeapon;
}

/* Metoda pobierajaca ilosc HP postaci*/
float AGCharacter::GetHealth()
{
	return Health;
}

/*	Metoda pobierajaca wynik meczu	//TODO:: Przenies do PlayerState */
int AGCharacter::GetScore()
{
	return Score;
}

/*	Metoda dodajaca punkt do wyniku	//TODO:: Przenies do PlayerState */
void AGCharacter::ScorePoint()
{
	AGGamePlayerController * pc = Cast<AGGamePlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
	if (pc)
	{
		AGPlayerState * ps = Cast<AGPlayerState >(pc->PlayerState);
		if (ps)
		{
			ps->ScorePoint();
			Score++;
		}
	}
}/*	*/

void AGCharacter::SetSkillA_Implementation(bool nSkillA)
{
	IsUsingSkillA = true;
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Skill A"));
	if(IsUsingSkillA)
		this->GetCharacterMovement()->MaxWalkSpeed = 2000;
	else
		this->GetCharacterMovement()->MaxWalkSpeed = 600;
}

void AGCharacter::SetSkillB_Implementation(bool nSkillA)
{

}

void AGCharacter::SetSkillC_Implementation(bool nSkillA)
{

}

/* Metoda potrzebna do replikacji */
void AGCharacter::GetLifetimeReplicatedProps(TArray< FLifetimeProperty > & OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AGCharacter, Health);
	DOREPLIFETIME(AGCharacter, Score);
	DOREPLIFETIME(AGCharacter, FPSWeapon);
	DOREPLIFETIME(AGCharacter, Weapon);
	DOREPLIFETIME(AGCharacter, IsFiring);
	DOREPLIFETIME(AGCharacter, IsReloading);
	DOREPLIFETIME(AGCharacter, IsUsingSkillA);
	DOREPLIFETIME(AGCharacter, IsUsingSkillB);
	DOREPLIFETIME(AGCharacter, IsUsingSkillC);
	DOREPLIFETIME(AGCharacter, IndexWeapon);
	DOREPLIFETIME(AGCharacter, WeaponBackpack);
	DOREPLIFETIME(AGCharacter, FireDelay);
	DOREPLIFETIME(AGCharacter, SkillADelay);
	DOREPLIFETIME(AGCharacter, SkillBDelay);
	DOREPLIFETIME(AGCharacter, SkillCDelay);
}