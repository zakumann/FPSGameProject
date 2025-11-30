// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapons/Pistol.h"
#include "Components/SkeletalMeshComponent.h"


void APistol::FireWeapon(const FVector& StartLocation, const FVector& ShootDirection)
{
	// Play the fire animation if it is set
	if (FireAnimation && GunMesh)
	{
		GunMesh->PlayAnimation(FireAnimation, false);
	}
	// Implement shooting logic here (e.g., spawn projectiles, apply damage, etc.)
}
