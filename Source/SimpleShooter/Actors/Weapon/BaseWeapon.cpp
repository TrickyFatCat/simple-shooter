// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseWeapon.h"

#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

ABaseWeapon::ABaseWeapon()
{
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	WeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Weapon Mesh"));
	WeaponMesh->SetupAttachment(Root);
}

void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
}

void ABaseWeapon::GetOutRotationAndLocation(FVector& OutLocation, FRotator& OutRotation)
{
	if (OwnerController == nullptr)
	{
		APawn* OwnerPawn = Cast<APawn>(GetOwner());
		if (OwnerPawn == nullptr) return;
		OwnerController = OwnerPawn->GetController();
	}
	
	if (OwnerController == nullptr) return;
	OwnerController->GetPlayerViewPoint(OutLocation, OutRotation);
}

bool ABaseWeapon::LineTraceShoot(FHitResult& OutHit, FVector Start, FVector End)
{
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor(this);
	CollisionQueryParams.AddIgnoredActor(GetOwner());
	
	bool bIsHit = GetWorld()->LineTraceSingleByChannel(
		OutHit,
		Start,
		End,
		ECC_GameTraceChannel1,
		CollisionQueryParams
	);
	
	return bIsHit;
}

bool ABaseWeapon::ApplyDamageToTarget(FRotator OutRotation, FHitResult& HitResult)
{
	FVector ShootDirection = -OutRotation.Vector();
	AActor* TargetActor = HitResult.GetActor();

	if (TargetActor)
	{
		UGameplayStatics::ApplyPointDamage(TargetActor, ShotDamage, ShootDirection, HitResult, OwnerController, this, DamageType);
		return true;
	}

	return false;
}

void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ABaseWeapon::PullTrigger()
{
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlashEffect, WeaponMesh, MuzzleSocket);
	UGameplayStatics::SpawnSoundAttached(MuzzleSound, WeaponMesh, MuzzleSocket);

	FVector OutLocation;
	FRotator OutRotation;
	GetOutRotationAndLocation(OutLocation, OutRotation);

	FVector EndPoint = OutLocation + OutRotation.Vector() * MaxShootRange;

	FHitResult OutHit;
	
	if (LineTraceShoot(OutHit, OutLocation, EndPoint))
	{
		FRotator NormalRotation = OutHit.Normal.Rotation();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, OutHit.Location, NormalRotation);
		UGameplayStatics::SpawnSoundAtLocation(GetWorld(), ImpactSound, OutHit.Location, NormalRotation);
		ApplyDamageToTarget(OutRotation, OutHit);
	}
}

void ABaseWeapon::SetShotDamage(float Value)
{
	ShotDamage = Value;
}

float ABaseWeapon::GetDamage() const
{
	return ShotDamage;
}
