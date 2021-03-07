// Fill out your copyright notice in the Description page of Project Settings.


#include "KillAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/AIControllers/BaseAIController.h"

void AKillAllGameMode::PawnKilled(APawn* Pawn)
{
	UE_LOG(LogTemp, Warning, TEXT("%s was killed."), *Pawn->GetName());
	APlayerController* PlayerController = Cast<APlayerController>(Pawn->GetController());

	if (PlayerController != nullptr)
	{
		ProcessEndGame(false);
	}

	for (ABaseAIController* Controller : TActorRange<ABaseAIController>(GetWorld()))
	{
		if (!Controller->IsControlledCharaterDead())
		{
			return;
		}
	}

	ProcessEndGame(true);
}

void AKillAllGameMode::ProcessEndGame(bool bIsPlayerWinner) 
{
	for (AController* Controller : TActorRange<AController>(GetWorld()))
	{
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
