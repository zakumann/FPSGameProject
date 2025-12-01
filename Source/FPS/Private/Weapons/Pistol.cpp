// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Pistol.h"
#include "Components/SkeletalMeshComponent.h"


APistol::APistol()
{
	// Single shot: no automatic repeat
	TimeBetweenShots = 0.f;
}

void APistol::FireWeapon(const FVector& StartLocation, const FVector& ShootDirection)
{
	// Play the fire animation if it is set
	if (FireAnimation && GunMesh)
	{
		GunMesh->PlayAnimation(FireAnimation, false);
	}
	
	Super::FireWeapon(StartLocation, ShootDirection);
}
