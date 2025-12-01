// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BaseWeapon.generated.h"

UCLASS()
class FPS_API ABaseWeapon : public AActor
{
	GENERATED_BODY()

public:
	ABaseWeapon();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon")
	class USkeletalMeshComponent* GunMesh;

protected:

	virtual void BeginPlay() override;

	// Time between shots in seconds (for automatic weapons)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Weapon")
	float TimeBetweenShots;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Weapon|Fire")
	bool bIsShooting;

	FTimerHandle TimerHandle_AutoFire;

	// Make FireWeapon public so AFPSCharacter can call it
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void FireWeapon(const FVector& StartLocation, const FVector& Direction);

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called by character when player starts shooting (pressed button)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StartShooting(const FVector& StartLocation, const FVector& ShootDirection);

	// Called by character when player stops shooting (released button)
	UFUNCTION(BlueprintCallable, Category = "Weapon")
	virtual void StopShooting();
};
