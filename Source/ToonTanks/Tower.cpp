// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); 

    if (InFireRange())
    {
        // If in range, rotate turret twoard Tank
        RotateTurret(Tank->GetActorLocation());         
    }

}

void ATower::BeginPlay()
{
    Super::BeginPlay(); 

    // Cast player0 pawn class to Tank variable as an ATank class to have Tower get access to Tank
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 

    // Set Timer to call Fire Condition
    GetWorldTimerManager().SetTimer(FireRateTimerHandle, this, &ATower::CheckFireCondition, FireRate, true); 

}

// Fire Condition Function to be called at end of Timer
void ATower::CheckFireCondition()
{
    if (InFireRange())
    {
        // If in range, call Fire function
        Fire();         
    }
    
}

bool ATower::InFireRange()
{
    if (Tank)
    {
        // Find the distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); 

        // Check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            return true; 
        }
    }

    return false; 
}