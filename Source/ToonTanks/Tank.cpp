// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Construct SpringArm Component and attach to RootComponent
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(RootComponent);  

    // Construct Camera Component and attach to SpringArm Component
	Camera= CreateDefaultSubobject<UCameraComponent>(TEXT("Camera")); 
	Camera->SetupAttachment(SpringArm); 

}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    
    // Binds Move function to MoveForward Axis Mapping
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move); 

    // Binds Turn function to Turn Axis Mapping
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn); 

    // Binds Fire function to Fire Action Mapping
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire);
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    if (PlayerControllerRef)
    {
        FHitResult HitResult;
        PlayerControllerRef->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);

        // Call RotateTurret Function from BasePawn to rotate towards HitResult.ImpactPoint by passing it in
        RotateTurret(HitResult.ImpactPoint); 

    }
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
    // GetController returns AController Object, a parent object of APlayerController, so it can be cast to an APlayerController type to be used in variable PlayerControllerRef
    PlayerControllerRef = Cast<APlayerController>(GetController()); 

}

void ATank::Move(float Value)
{
    // Have tank move backwards and forwards on local x-axis by PlayerInput Value
    FVector DeltaLocation(0.f); 
    // X = Value * DeltaTime * Speed; Makes movement independent of DeltaTime or FrameRate
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this); 
    DeltaLocation.X = Value * Speed * DeltaTime;
    AddActorLocalOffset(DeltaLocation, true); 
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator;
    // Yaw = Value * DeltaTime * TurnRate; makes rotation on z-axis independent of DeltaTime or FrameRate
    float DeltaTime = UGameplayStatics::GetWorldDeltaSeconds(this);
    DeltaRotation.Yaw = Value * TurnRate * DeltaTime; 
    AddActorLocalRotation(DeltaRotation, true); 
}