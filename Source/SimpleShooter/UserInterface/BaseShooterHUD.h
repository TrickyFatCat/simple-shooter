// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BaseShooterHUD.generated.h"

class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API ABaseShooterHUD : public AHUD
{
	GENERATED_BODY()

public:
	void ShowResultScreen(bool bPlayerWon);

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, Category="Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> PlayerHUDClass;
	UPROPERTY(EditAnywhere, Category="Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> LoseScreenClass;
	UPROPERTY(EditAnywhere, Category="Widgets", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WinScreenClass;

	UUserWidget* PlayerHud = nullptr;

	UUserWidget* CreateAndAddWidget(TSubclassOf<UUserWidget> UserWidget, FName WidgetName);
};
