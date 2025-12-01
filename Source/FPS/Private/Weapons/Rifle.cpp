// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Rifle.h"
#include "Components/SkeletalMeshComponent.h"

ARifle::ARifle()
{
	// Faster fire rate: e.g. 900 RPM ≈ 0.066 sec per shot
	TimeBetweenShots = 0.08f; // adjust as you like
}

void ARifle::FireWeapon(const FVector& StartLocation, const FVector& ShootDirection)
{
	// TODO: play Rifle-specific animation, muzzle flash etc.

	// Call base to do the actual line trace + debug
	Super::FireWeapon(StartLocation, ShootDirection);
}