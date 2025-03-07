// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InputActionValue.h"
#include "FPSWeaponBaseComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class FPS_API UFPSWeaponBaseComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UFPSWeaponBaseComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	// Fire Raycast
	void Fire();

	// Reference to the owning player character
	UPROPERTY()
	class APlayerCharacter* OwnerCharacter;

	// Bind Enhanced Input
	void SetupEnhancedInput();

public:	
	// Fire range
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float FireRange = 5000.0f;

	// Damage amount
	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	float DamageAmount = 50.0f;
		
	// Input Action for Fire
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Input")
	class UInputAction* FireAction;
};
