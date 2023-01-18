// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:

	virtual void Tick(float DeltaTime) override; 

	// Function to destroy dead Towers called from Game Mode
	void HandleDestruction();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	// Forward declare pointer to tank for Tower to aim at it
	class ATank* Tank; 

	// Create FireRange variable for distance limit of when Tower can fire
	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 700.f; 

	// Timer Parameters for Tower Fire SetTimer()
	FTimerHandle FireRateTimerHandle; 
	float FireRate =2.f; 
	void CheckFireCondition(); 

	// Refactor check if tank in range of tower
	bool InFireRange();
};
