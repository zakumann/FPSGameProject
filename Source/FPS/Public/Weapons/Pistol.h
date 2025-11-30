// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapons/BaseWeapon.h"
#include "Pistol.generated.h"

/**
 * 
 */
UCLASS()
class FPS_API APistol : public ABaseWeapon
{
	GENERATED_BODY()

public:
	// Animation to play when firing
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon|Animation")
	class UAnimationAsset* FireAnimation;

	// FireWeapon
	virtual void FireWeapon(const FVector& StartLocation, const FVector& ShootDirection);
};
