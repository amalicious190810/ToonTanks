// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ToonTanksGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API AToonTanksGameMode : public AGameModeBase
{
	GENERATED_BODY()

public: 

// Declare ActorDied function to be called from HealthComponent class when DamageTaken
void ActorDied(AActor* DeadActor); 

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override; 

private:

	// Forward declare tank variable to check if the dead actor is a tank
	class ATank* Tank; 

};
