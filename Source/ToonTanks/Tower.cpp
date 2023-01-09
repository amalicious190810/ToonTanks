// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"

void ATower::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime); 

    if (Tank)
    {
        
        // Find the distance to the tank
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation()); 

        // Check to see if the Tank is in range
        if (Distance <= FireRange)
        {
            // If in range, rotate turret twoard Tank
            RotateTurret(Tank->GetActorLocation());         
        }
    }

}

void ATower::BeginPlay()
{
    Super::BeginPlay(); 

    // Cast player0 pawn class to Tank variable as an ATank class to have Tower get access to Tank
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); 

}
