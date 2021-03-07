// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShooterGameMode.h"

void ABaseShooterGameMode::PawnKilled(APawn* Pawn)
{
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (PlayerController != nullptr)
	{
		PlayerController->GameHasEnded(nullptr, false);
	}
}
