// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseShooterGameMode.h"
#include "KillAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillAllGameMode : public ABaseShooterGameMode
{
	GENERATED_BODY()

public:
	virtual void PawnKilled(APawn* Pawn) override;

private:
	void ProcessEndGame(bool bIsPlayerWinner);
	
};
