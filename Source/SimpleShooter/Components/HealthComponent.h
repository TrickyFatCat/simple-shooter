// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class SIMPLESHOOTER_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	UHealthComponent();

	float GetCurrentHealth() const;
	float GetMaxHealth() const;
	
	UFUNCTION(BlueprintCallable)
	float DecreaseCurrentHealth(float Amount);
	UFUNCTION(BlueprintCallable)
	float IncreaseCurrentHealth(float Amount, bool bClampToMax);
	UFUNCTION(BlueprintCallable)
	float DecreaseMaxHealth(float Amount, bool bClampCurrent);
	UFUNCTION(BlueprintCallable)
	float IncreaseMaxHealth(float Amount, bool bRestoreCurrent);
	UFUNCTION(BlueprintCallable)
	float GetNolmalizedHealth();

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Health Parameters", meta = (AllowPrivateAccess = "true", ClampMin = "1.0"))
	float MaxHealth = 100.f;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Health Parameters", meta = (AllowPrivateAccess = "true"))
	float CurrentHealth = 100.f;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Parameters", meta = (AllowPrivateAccess = "true"))
	bool bCustomInitialHealth = false;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Health Parameters", meta = (AllowPrivateAccess = "true", ClampMin = "1.0", EditCondition = "bCustomInitialHealth"))
	float InitialHealth = 100.f;
};
