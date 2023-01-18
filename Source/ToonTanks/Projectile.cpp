// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	// Construct Projectile Static Mesh Component and assignt to Root Component 
	// Assigne CapsuleComp to Root Component
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh")); 
	RootComponent = ProjectileMesh;

	// Construct Projectile Movement Component and attach to RootComponent
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement"));
	ProjectileMovementComponent->MaxSpeed = 1300.f; 
	ProjectileMovementComponent->InitialSpeed = 1300.f; 

}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
	// Bind OnHit function to OnComponentHit multicast delegate
	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); 

}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Define OnHit callback function 
void AProjectile::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Set local variable that stores pointer of owner actor of each projectile
	auto MyOwner = GetOwner(); 
	if (MyOwner == nullptr) return; 

	// Access InstigatorController for ApplyDamage through projectile's owner actor
	auto MyOwnerInstigator = MyOwner->GetInstigatorController();

	// Get pointer to UClass of UDamageType to pass into ApplyDamage
	auto DamageTypeClass = UDamageType::StaticClass(); 

	// Place checks to make sure it's appropriate to call ApplyDamage function
	// Make sure OtherActor isn't null
	// Avoid ApplyingDamage to the projectile by making sure OtherActor isn't the same as this actor, the projectile
	// Avoid ApplyingDamage to projectile's owner actor by making sure OtherActor isn't the same as the owner of the projectile
	if(OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Call ApplyDamage to generate damage event so that the OnTakeAnyDamage delegate in HealthComponent will broadcast and call DamageTaken
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass); 

		// Destroy projectile after it hits something
		Destroy(); 
	}
}
