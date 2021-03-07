// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"


#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "SimpleShooter/PlayerControllers/PlayerCharacterController.h"
#include "SimpleShooter/Actors/Weapon/BaseWeapon.h"

APlayerCharacter::APlayerCharacter()
{
	SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArmComponent->SetupAttachment(RootComponent);

	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComponent->SetupAttachment(SpringArmComponent);
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APlayerCharacter::MoveRight);
	PlayerInputComponent->BindAxis("LookUp", this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("LookUpGp", this, &APlayerCharacter::LookUpGamepad);
	PlayerInputComponent->BindAxis("LookRight", this, &APawn::AddControllerYawInput);
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APlayerCharacter::Jump);
	PlayerInputComponent->BindAction("Shoot", IE_Pressed, this, &APlayerCharacter::Shoot);
}

void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerCharacterController = Cast<APlayerCharacterController>(CharacterController);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void APlayerCharacter::LookUpGamepad(float AxisValue)
{
	AddControllerPitchInput(
		AxisValue * PlayerCharacterController->GetGamepadVerticalSence() * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookRightGamepad(float AxisValue)
{
	AddControllerYawInput(
		AxisValue * PlayerCharacterController->GetGamepadHorizontalSence() * GetWorld()->GetDeltaSeconds());
}
