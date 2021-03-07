// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BaseAIController.generated.h"

class UBehaviorTree;
class UBlackboardComponent;

UCLASS()
class SIMPLESHOOTER_API ABaseAIController : public AAIController
{
	GENERATED_BODY()

public:
	virtual void Tick(float DeltaSeconds) override;
	
	UFUNCTION(BlueprintPure)
	bool IsControlledCharaterDead() const;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Controller Parameters",
		meta = (AllowPrivateAccess = "true"))
	UBehaviorTree* AIBehavior = nullptr;
};
