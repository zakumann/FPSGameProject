// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "Rifle.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API ARifle : public ABaseWeapon
{
	GENERATED_BODY()
	
public:
	ARifle();

	// If you want Rifle-specific behavior, you can override FireWeapon here
	virtual void FireWeapon(const FVector& StartLocation, const FVector& ShootDirection) override;
};
