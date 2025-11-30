// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/BaseWeapon.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"

// Sets default values
ABaseWeapon::ABaseWeapon()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GunMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("GunMesh"));
	GunMesh->SetupAttachment(RootComponent);

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

void ABaseWeapon::FireWeapon(const FVector& StartLocation, const FVector& ShootDirection)
{
	if (!GetWorld()) return;

	FVector Direction = ShootDirection.GetSafeNormal();
	FVector EndLocation = StartLocation + (Direction * 3000.0f);

	FHitResult HitResult;

	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(this); // Ignore the weapon itself
	bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation, ECC_Visibility, QueryParams);
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

