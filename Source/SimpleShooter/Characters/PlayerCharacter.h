// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BaseCharacter.h"

#include "PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;
class APlayerCharacterController;

UCLASS()
class SIMPLESHOOTER_API APlayerCharacter : public ABaseCharacter
{
	GENERATED_BODY()

public:
	APlayerCharacter();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	virtual void BeginPlay() override;

private:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArmComponent;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* CameraComponent;

	APlayerCharacterController* PlayerCharacterController;

	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpGamepad(float AxisValue);
	void LookRightGamepad(float AxisValue);
};
