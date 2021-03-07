// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseAIController.h"

#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/EnemyCharacter.h"

void ABaseAIController::BeginPlay()
{
	Super::BeginPlay();

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

	if (AIBehavior != nullptr)
	{
		RunBehaviorTree(AIBehavior);

		if (GetBlackboardComponent() != nullptr)
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("PlayerPawn"), PlayerPawn);
			GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), GetPawn()->GetActorLocation());
		}
	}
}


void ABaseAIController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

bool ABaseAIController::IsControlledCharaterDead() const
{
	AEnemyCharacter* ControlledCharacter = Cast<AEnemyCharacter>(GetPawn());

	if (ControlledCharacter != nullptr)
	{
		return ControlledCharacter->IsDead();
	}

	return true;
}
