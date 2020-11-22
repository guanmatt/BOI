// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ProjectileBase.h"
#include "BOIPlayerController.generated.h"

UCLASS()
class ABOIPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ABOIPlayerController();

protected:
	/** True if the controlled character should navigate to the mouse cursor. */
	uint32 bMoveToMouseCursor : 1;

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// Projectile class to spawn.
	UPROPERTY(EditDefaultsOnly, Category = Projectile)
	TSubclassOf<class AProjectileBase> ProjectileClass;
	// End PlayerController interface

	/** Resets HMD orientation in VR. */
	// void OnResetVR();

	/** Navigate player to the current mouse cursor location. */
	// void MoveToMouseCursor();
public:
	UFUNCTION()
	void MoveRight(float Value);
	UFUNCTION()
	void MoveForward(float Value);
	UFUNCTION()
	void Fire();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Gameplay)
	FVector MuzzleOffset;
	/** Navigate player to the current touch location. */
	// void MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location);
	
	/** Navigate player to the given world location. */
	// void SetNewMoveDestination(const FVector DestLocation);

	/** Input handlers for SetDestination action. */
	// void OnSetDestinationPressed();
	// void OnSetDestinationReleased();
};


