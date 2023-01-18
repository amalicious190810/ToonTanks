// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Tower.h"

// Define ActorDied function to be called from HealthComponent class when DamageTaken
void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    // Check to see if dead actor is Tank
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction();

        // Check to see if TankPlayerController pointer is null
        if (Tank->GetTankPlayerController())
        {
            // Disable input for Tank
            Tank->DisableInput(Tank->GetTankPlayerController());

            // Make sure mouse cursor isn't shown
            Tank->GetTankPlayerController()->bShowMouseCursor = false;
        }
    }
    // Check to see if dead actor is Tower instance by seeing if DeadActor can be cast ATower class
    else if(ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        // Destroy dead tower
        DestroyedTower->HandleDestruction(); 
    }
} 

// Called when the game starts or when spawned
void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay(); 

    // Get pointer to player pawn in form of ATank
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 
}
