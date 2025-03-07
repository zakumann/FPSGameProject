// Fill out your copyright notice in the Description page of Project Settings.


#include "FPSWeaponBaseComponent.h"
#include "PlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "InputMappingContext.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/DamageType.h"

// Sets default values for this component's properties
UFPSWeaponBaseComponent::UFPSWeaponBaseComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UFPSWeaponBaseComponent::BeginPlay()
{
	Super::BeginPlay();

	// Get the owning character
	OwnerCharacter = Cast<APlayerCharacter>(GetOwner());
	
	// Setup Enhanced Input
	SetupEnhancedInput();
}


void UFPSWeaponBaseComponent::SetupEnhancedInput()
{
	if (!OwnerCharacter) return;

	APlayerController* PlayerController = Cast<APlayerController>(OwnerCharacter->GetController());
	if (!PlayerController) return;

	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
	if (!InputSubsystem) return;

	UInputComponent* InputComponent = OwnerCharacter->InputComponent;
	if (!InputComponent) return;

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!EnhancedInputComponent) return;

	// Bind Fire Action
	if (FireAction)
	{
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &UFPSWeaponBaseComponent::Fire);
	}
}

void UFPSWeaponBaseComponent::Fire()
{
	if (OwnerCharacter)
	{
		if (!OwnerCharacter || !OwnerCharacter->FirstPersonCamera) return;

		FVector CameraLocation = OwnerCharacter->FirstPersonCamera->GetComponentLocation();
		FVector CameraForward = OwnerCharacter->FirstPersonCamera->GetForwardVector();
		FVector EndLocation = CameraLocation + (CameraForward * FireRange);

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(OwnerCharacter);

		if (GetWorld()->LineTraceSingleByChannel(HitResult, CameraLocation, EndLocation, ECC_Visibility, QueryParams))
		{
			AActor* HitActor = HitResult.GetActor();
			if (HitActor)
			{
				UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitActor->GetName());
				UGameplayStatics::ApplyDamage(HitActor, DamageAmount, OwnerCharacter->GetController(), OwnerCharacter, UDamageType::StaticClass());
			}
		}

		// Debug line
		DrawDebugLine(GetWorld(), CameraLocation, EndLocation, FColor::Red, false, 1.0f, 0, 2.0f);
	}
}