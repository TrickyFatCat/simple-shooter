// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BaseCharacter.generated.h"

class ABaseWeapon;
class UHealthComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	ABaseCharacter();
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	                         AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure)
	bool IsDead() const;
	UFUNCTION(BlueprintPure)
	float GetHealthPercent() const;

	void Shoot();
	
protected:
	virtual void BeginPlay() override;
	UPROPERTY(BlueprintReadOnly, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	ABaseWeapon* Weapon;

	AController* CharacterController;

	virtual void ProcessDeath();

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<ABaseWeapon> WeaponClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Weapons", meta = (AllowPrivateAccess = "true"))
	UHealthComponent* HealthComponent = nullptr;
};
