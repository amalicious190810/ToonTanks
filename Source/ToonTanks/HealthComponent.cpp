// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthComponent.h"

// Sets default values for this component's properties
UHealthComponent::UHealthComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	// Start Health variable at Maximum Health default value
	Health = MaxHealth; 
	
	// Bind DamageTaken callback function to OnTakeAnyDamage delegate (already exists on pawn that owns health component)
	// Now when damage events are generated, OnTakeAnyDamage delegate will broadcast to all functions on inovcation list, including DamageTaken function, to be called
	GetOwner()->OnTakeAnyDamage.AddDynamic(this, &UHealthComponent::DamageTaken);
}


// Called every frame
void UHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// Define Callback function to bind to OnTakeAnyDamage delegate on pawn/actor that owns this HealthComponent
void UHealthComponent::DamageTaken(AActor* DamagedActor, float Damage, const UDamageType* DamageType, class AController* Instigator, AActor* DamageCauser)
{
	// Check that damage is greater than zero before reducing Health
	if (Damage <= 0.f) return;

	// Subtract damage from DamagedActor's Health variable
	Health -= Damage;

	UE_LOG(LogTemp, Warning, TEXT("Health: %f"), Health); 
	  
}
