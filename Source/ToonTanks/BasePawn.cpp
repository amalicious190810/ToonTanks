// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct Capsule Component for collisions and save pointer to CapsuleComp
	// Assigne CapsuleComp to Root Component
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider")); 
	RootComponent = CapsuleComp;

	// Construct Tank Static Mesh Components and attach to CapsuleComp/BaseMesh
	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);  

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh")); 
	TurretMesh->SetupAttachment(BaseMesh); 

	// Construct Projectile Scene Component and attach to Turret Mesh
	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Projectile Spawn Point")); 
	ProjectileSpawnPoint->SetupAttachment(TurretMesh); 

}

// Function to rotate Turret Meshes on Tank and AI Turrets
void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	// Vector from turret component to trace hit result under mouse cursor
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation(); 

	// Rotator to roatate only on Yaw towards ToTarget Vector
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f);

	// Set Rotation for TurretMesh with interpolate for smooth rotation
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(
			TurretMesh->GetComponentRotation(), 
			LookAtRotation, 
			UGameplayStatics::GetWorldDeltaSeconds(this), 
			5.f)
		); 
}

// Function to Fire projectiles on Tank and Tower
void ABasePawn::Fire()
{
	   // Get the Projectile's spawn point location
	   FVector ProjectileSpawnPointLocation = ProjectileSpawnPoint->GetComponentLocation();
	   
	   // Draw a Debug Sphere using trace result under cursor
        DrawDebugSphere(
        GetWorld(), 
        ProjectileSpawnPointLocation, 
        25.f, 
        12, 
        FColor::Red, 
        false, 
        3.f); 
}