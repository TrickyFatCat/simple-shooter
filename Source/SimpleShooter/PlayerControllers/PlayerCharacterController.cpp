// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"

#include "TimerManager.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/UserInterface/BaseShooterHUD.h"


void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerCharacterController::SetGamepadVerticalSence(float Value)
{
	GamepadVerticalSence = Value;
}

float APlayerCharacterController::GetGamepadVerticalSence()
{
	return GamepadVerticalSence;
}

void APlayerCharacterController::SetGamepadHorizontalSence(float Value)
{
	GamepadHorizontalSence = Value;
}

float APlayerCharacterController::GetGamepadHorizontalSence()
{
	return GamepadHorizontalSence;
}

void APlayerCharacterController::GameHasEnded(AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);

	ABaseShooterHUD* PlayerHUD = Cast<ABaseShooterHUD>(GetHUD());
	if (PlayerHUD != nullptr)
	{
		PlayerHUD->ShowResultScreen(bIsWinner);
	}

	GetWorldTimerManager().SetTimer(RestartTimer, this, &APlayerController::RestartLevel, RestartTime);
}

void APlayerCharacterController::SetRestartTime(float Time)
{
	if (Time < 0)
	{
		Time = FMath::Abs(Time);
		UE_LOG(LogBlueprint, Warning, TEXT("Restart time can't be less than 0. Time was converted."));
	}

	RestartTime = Time;
}