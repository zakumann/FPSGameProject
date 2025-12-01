// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

// simple cached values for timer use (can be refactored later if you want)
static FVector G_LastStartLocation;
static FVector G_LastShootDirection;

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);

	// Default automatic weapon: 600 RPM -> 0.1 seconds per shot
	TimeBetweenShots = 0.1f;
	bIsShooting = false;
}

// Called when the game starts or when spawned
void ABaseWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABaseWeapon::StartShooting(const FVector& StartLocation, const FVector& ShootDirection)
{
	if (!GetWorld())
	{
		return;
	}

	// cache camera data for timer use
	G_LastStartLocation = StartLocation;
	G_LastShootDirection = ShootDirection;

	// fire immediately once
	FireWeapon(StartLocation, ShootDirection);

	// If TimeBetweenShots <= 0, treat as single-shot weapon (no auto-fire)
	if (TimeBetweenShots <= 0.f)
	{
		return;
	}

	if (!bIsShooting)
	{
		bIsShooting = true;

		// Start looping timer for automatic fire
		GetWorldTimerManager().SetTimer(
			TimerHandle_AutoFire,
			[this]()
			{
				FireWeapon(G_LastStartLocation, G_LastShootDirection);
			},
			TimeBetweenShots,
			true
		);
	}
}

void ABaseWeapon::StopShooting()
{
	if (!GetWorld())
	{
		return;
	}

	if (bIsShooting)
	{
		bIsShooting = false;
		GetWorldTimerManager().ClearTimer(TimerHandle_AutoFire);
	}
}

void ABaseWeapon::FireWeapon(const FVector& StartLocation, const FVector& ShootDirection)
{
	if (!GetWorld()) return;

	FVector Direction = ShootDirection.GetSafeNormal();
	FVector EndLocation = StartLocation + (Direction * 3000.0f);

	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the weapon itself

	// Ignore owner (character) so we don't hit ourselves
	if (AActor* MyOwner = GetOwner())
	{
		QueryParams.AddIgnoredActor(MyOwner);
	}

	bool bHit = GetWorld()->LineTraceSingleByChannel(
		HitResult,
		StartLocation,
		EndLocation,
		ECC_Visibility,
		QueryParams
	);

	if (bHit)
	{
		// Draw debug line to the hit location
		DrawDebugLine(GetWorld(), StartLocation, HitResult.Location, FColor::Red, false, 2.0f);
		DrawDebugSphere(GetWorld(), HitResult.Location, 10.0f, 12, FColor::Green, false, 2.0f);
		// You can add logic here to apply damage or effects to the hit actor
	}
	else
	{
		// Draw debug line to the end location if no hit
		DrawDebugLine(GetWorld(), StartLocation, EndLocation, FColor::Blue, false, 2.0f);
	}
}

