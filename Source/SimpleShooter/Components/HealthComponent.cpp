// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"


UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

float UHealthComponent::GetCurrentHealth() const
{
	return CurrentHealth;
}

float UHealthComponent::GetMaxHealth() const
{
	return MaxHealth;
}

float UHealthComponent::DecreaseCurrentHealth(float Amount)
{
	return CurrentHealth = FMath::Max(CurrentHealth - Amount, 0.f);
}

float UHealthComponent::IncreaseCurrentHealth(float Amount, bool bClampToMax)
{
	CurrentHealth += Amount;

	if (bClampToMax)
	{
		CurrentHealth = FMath::Min(CurrentHealth, MaxHealth);
	}

	return CurrentHealth;
}

float UHealthComponent::DecreaseMaxHealth(float Amount, bool bClampCurrent)
{
	MaxHealth -= FMath::Max(MaxHealth, 1.f);

	if (bClampCurrent)
	{
		CurrentHealth = MaxHealth;
	}

	return MaxHealth;
}

float UHealthComponent::IncreaseMaxHealth(float Amount, bool bRestoreCurrent)
{
	MaxHealth += Amount;

	if (bRestoreCurrent)
	{
		CurrentHealth = MaxHealth;
	}

	return MaxHealth;
}

float UHealthComponent::GetNolmalizedHealth()
{
	return CurrentHealth / MaxHealth;
}


void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (bCustomInitialHealth)
	{
		CurrentHealth = InitialHealth;
	}
	
	if (MaxHealth < CurrentHealth)
	{
		UE_LOG(LogTemp, Warning, TEXT("MaxHealth is less than CurrentHealth in %s. Check %s adjustments."),
		       *GetOwner()->GetName(), *GetName());
	}
}
