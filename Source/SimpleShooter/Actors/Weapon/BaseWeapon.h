// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ABaseWeapon();
	virtual void Tick(float DeltaTime) override;
	void PullTrigger();
	void SetShotDamage(float Value);
	float GetDamage() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* Root;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USkeletalMeshComponent* WeaponMesh;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* MuzzleFlashEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects", meta = (AllowPrivateAccess = "true"))
	UParticleSystem* ImpactEffect = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* MuzzleSound = nullptr;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Effects", meta = (AllowPrivateAccess = "true"))
	USoundBase* ImpactSound = nullptr;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Shoot Parameters", meta = (AllowPrivateAccess = "true"))
	float ShotDamage = 10.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Shoot Parameters", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float MaxShootRange = 5000.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Shoot Parameters", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UDamageType> DamageType;

	AController* OwnerController = nullptr;
	const FName MuzzleSocket = TEXT("MuzzleFlashSocket");

	void GetOutRotationAndLocation(FVector& OutLocation, FRotator& OutRotation);
	bool LineTraceShoot(FHitResult& OutHit, FVector Start, FVector End);
	bool ApplyDamageToTarget(FRotator OutRotation, FHitResult& HitResult);
};
