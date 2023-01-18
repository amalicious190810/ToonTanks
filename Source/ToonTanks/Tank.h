// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Function to destroy dead Tank called from Game Mode
	void HandleDestruction();

	// Declare a public getter function for tank player controller to pass into disable input function in ToonTanksGameMode
	APlayerController* GetTankPlayerController() const { return TankPlayerController; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
// Add Spring Arm Component and Camera Component to Tank
// Forward Declare Spring Arm and Camera Component pointers

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera;  

// Speed Variable to control Tank's X movement multiplier independent of Frame Rate
	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 200.f; 

// TurnRate Variable to control Tank's Yaw rotation multiplier independent of Frame Rate
	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f; 

// Move Function that takes in float from Player Input and binds to MoveForward Axis Mapping
	void Move(float Value);

// Turn Function that takes in float from Player Input and binds to Turn Axis Mapping
	void Turn(float Value);

	APlayerController* TankPlayerController; 
};
