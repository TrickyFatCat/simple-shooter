// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacterController.generated.h"

class UUserWidget;

UCLASS()
class SIMPLESHOOTER_API APlayerCharacterController : public APlayerController
{
	GENERATED_BODY()

public:
	void SetGamepadVerticalSence(float Value);
	float GetGamepadVerticalSence();
	void SetGamepadHorizontalSence(float Value);
	float GetGamepadHorizontalSence();
	virtual void GameHasEnded(AActor* EndGameFocus, bool bIsWinner) override;

	UFUNCTION(BlueprintCallable)
	void SetRestartTime(float NewTime);


protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls Options", meta = (AllowPrivateAccess = "true"))
	float GamepadHorizontalSence = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Controls Options", meta = (AllowPrivateAccess = "true"))
	float GamepadVerticalSence = 10.f;
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Restart Parameters", meta = (AllowPrivateAccess = "true", ClampMin = "0.0"))
	float RestartTime = 5.f;

	FTimerHandle RestartTimer;
};
