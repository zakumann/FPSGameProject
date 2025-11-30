// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/FPSAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"  
#include "Character/FPSCharacter.h"

void UFPSAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	PlayerCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
}

void UFPSAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);

	if (!PlayerCharacter)
	{
		PlayerCharacter = Cast<AFPSCharacter>(TryGetPawnOwner());
	}
	if (PlayerCharacter)
	{
		FVector Velocity = PlayerCharacter->GetVelocity();
		Velocity.Z = 0; // Ignore vertical velocity
		Speed = Velocity.Size();

		// 2) In-air flag (jumping / falling)
		if (const UCharacterMovementComponent* MoveComp = PlayerCharacter->GetCharacterMovement())
		{
			// IsFalling() == true when character is not on ground
			bIsInAir = MoveComp->IsFalling();
		}
		else
		{
			bIsInAir = false;
		}
	}
	else
	{
		// If no character, set safe defaults
		Speed = 0.f;
		bIsInAir = false;
	}
}
