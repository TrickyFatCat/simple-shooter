// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseCharacter.h"


#include "Components/CapsuleComponent.h"
#include "SimpleShooter/Actors/Weapon/BaseWeapon.h"
#include "SimpleShooter/Components/HealthComponent.h"
#include "SimpleShooter/GameModes/BaseShooterGameMode.h"

ABaseCharacter::ABaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	HealthComponent = CreateDefaultSubobject<UHealthComponent>(TEXT("Health Component"));
}

void ABaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	CharacterController = GetController();

	GetMesh()->HideBoneByName(TEXT("weapon_r"), PBO_None);
	if (!WeaponClass)
	{
		UE_LOG(LogTemp, Error, TEXT("Weapon class is null. Please adjust weapon class to spawn in %s"),
		       *(GetClass()->GetName()));
		return;
	}
	Weapon = GetWorld()->SpawnActor<ABaseWeapon>(WeaponClass);
	Weapon->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Weapon->SetOwner(this);
}

void ABaseCharacter::Shoot()
{
	Weapon->PullTrigger();
}

void ABaseCharacter::ProcessDeath()
{
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	ABaseShooterGameMode* GameMode = GetWorld()->GetAuthGameMode<ABaseShooterGameMode>();

	if (GameMode != nullptr)
	{
		GameMode->PawnKilled(this);
	}
	
	DetachFromControllerPendingDestroy();
}

void ABaseCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float ABaseCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
                                 AActor* DamageCauser)
{
	float IncomingDamage = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	if (IsDead())
	{
		return IncomingDamage;
	}
	
	HealthComponent->DecreaseCurrentHealth(IncomingDamage);
	UE_LOG(LogTemp, Warning, TEXT("Actor %s has %f/%f health."), *(GetName()), HealthComponent->GetCurrentHealth(), HealthComponent->GetMaxHealth());

	if (IsDead())
	{
		ProcessDeath();
	}
	
	return IncomingDamage;
}

bool ABaseCharacter::IsDead() const
{
	return HealthComponent->GetCurrentHealth() <= 0.f;
}

float ABaseCharacter::GetHealthPercent() const
{
	return HealthComponent->GetNolmalizedHealth();
}
