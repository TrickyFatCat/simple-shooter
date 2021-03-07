// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseShooterHUD.h"
#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void ABaseShooterHUD::BeginPlay()
{
	Super::BeginPlay();

	PlayerHud = CreateAndAddWidget(PlayerHUDClass, TEXT("Player HUD"));
}

void ABaseShooterHUD::ShowResultScreen(bool bPlayerWon)
{
	PlayerHud->RemoveFromViewport();

	if (bPlayerWon)
	{
		CreateAndAddWidget(WinScreenClass, TEXT("Win Screen"));
	}
	else
	{
		CreateAndAddWidget(LoseScreenClass, TEXT("Loose Screen"));
	}
}

UUserWidget* ABaseShooterHUD::CreateAndAddWidget(TSubclassOf<UUserWidget> UserWidget, FName WidgetName)
{
	UUserWidget* ResultScreen = CreateWidget(UGameplayStatics::GetPlayerController(GetWorld(), 0), UserWidget, WidgetName);
	if (ResultScreen != nullptr)
	{
		ResultScreen->AddToViewport();
		return ResultScreen;
	}

	return nullptr;
}
