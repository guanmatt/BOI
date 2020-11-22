// Copyright Epic Games, Inc. All Rights Reserved.

#include "GameFramework/Pawn.h"
#include "BOIPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/Controller.h"
#include "BOICharacter.h"
#include "Math/Vector.h"
#include "Engine/World.h"

ABOIPlayerController::ABOIPlayerController()
{
	bShowMouseCursor = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ABOIPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	// keep updating the destination every tick while desired
	// if (bMoveToMouseCursor)
	// {
	// 	MoveToMouseCursor();
	// }
}

void ABOIPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();

	InputComponent->BindAction("Fire", IE_Pressed, this, &ABOIPlayerController::Fire);
	// InputComponent->BindAction("Fire", IE_Released, this, &ABOIPlayerController::OnSetDestinationReleased);
	// support touch devices 
	// InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &ABOIPlayerController::MoveToTouchLocation);
	// InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &ABOIPlayerController::MoveToTouchLocation);
	// InputComponent->BindAction("ResetVR", IE_Pressed, this, &ABOIPlayerController::OnResetVR);

	InputComponent->BindAxis("MoveForward", this, &ABOIPlayerController::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &ABOIPlayerController::MoveRight);

}
/*
	void ABOIPlayerController::OnResetVR()
	{
		UHeadMountedDisplayFunctionLibrary::ResetOrientationAndPosition();
	}

	void ABOIPlayerController::MoveToMouseCursor()
	{
		if (UHeadMountedDisplayFunctionLibrary::IsHeadMountedDisplayEnabled())
		{
			if (ABOICharacter* MyPawn = Cast<ABOICharacter>(GetPawn()))
			{
				if (MyPawn->GetCursorToWorld())
				{
					UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, MyPawn->GetCursorToWorld()->GetComponentLocation());
				}
			}
		}
		else
		{
			// Trace to see what is under the mouse cursor
			FHitResult Hit;
			GetHitResultUnderCursor(ECC_Visibility, false, Hit);

			if (Hit.bBlockingHit)
			{
				// We hit something, move there
				SetNewMoveDestination(Hit.ImpactPoint);
			}
		}
	}

	void ABOIPlayerController::MoveToTouchLocation(const ETouchIndex::Type FingerIndex, const FVector Location)
	{
		FVector2D ScreenSpaceLocation(Location);

		// Trace to see what is under the touch location
		FHitResult HitResult;
		GetHitResultAtScreenPosition(ScreenSpaceLocation, CurrentClickTraceChannel, true, HitResult);
		if (HitResult.bBlockingHit)
		{
			// We hit something, move there
			SetNewMoveDestination(HitResult.ImpactPoint);
		}
	}

	void ABOIPlayerController::SetNewMoveDestination(const FVector DestLocation)
	{
		APawn* const MyPawn = GetPawn();
		if (MyPawn)
		{
			float const Distance = FVector::Dist(DestLocation, MyPawn->GetActorLocation());

			// We need to issue move command only if far enough in order for walk animation to play correctly
			if ((Distance > 120.0f))
			{
				UAIBlueprintHelperLibrary::SimpleMoveToLocation(this, DestLocation);
			}
		}
	}

	void ABOIPlayerController::OnSetDestinationPressed()
	{
		// set flag to keep updating destination until released
		bMoveToMouseCursor = true;
	}

	void ABOIPlayerController::OnSetDestinationReleased()
	{
		// clear flag to indicate we should stop updating the destination
		bMoveToMouseCursor = false;
	}
	*/
void ABOIPlayerController::MoveRight(float Value)
{
	FVector Direction(0, 90 ,0);
	GetPawn()->AddMovementInput(Direction, Value);
}

void ABOIPlayerController::MoveForward(float Value)
{
	FVector Direction(90, 00 ,0);
	GetPawn()->AddMovementInput(Direction, Value);
}

void ABOIPlayerController::Fire()
{
	FHitResult HitResult;
	GetHitResultUnderCursor(ECC_Visibility, false, HitResult);

	if (HitResult.bBlockingHit)
	{
		GetHitResultUnderCursor(ECC_Visibility, false, HitResult);
		FVector CursorLocation = HitResult.Location;
		UE_LOG(LogTemp, Warning, TEXT("Mouse position: %s"), *CursorLocation.ToString());
		UWorld* const World = GetWorld();
		if (World)
		{
			FActorSpawnParameters SpawnParams;
			SpawnParams.Owner = GetPawn();
			SpawnParams.Instigator = GetPawn()->GetInstigator();

			FVector CameraLocation;
			FRotator CameraRotation;
			GetActorEyesViewPoint(CameraLocation, CameraRotation);
			// UE_LOG(LogTemp, Warning, TEXT("%s"), *CameraLocation.ToString());
			AProjectileBase* Projectile = World->SpawnActor<AProjectileBase>(CameraLocation, CameraRotation, SpawnParams);
			if (Projectile)
			{
				UE_LOG(LogTemp, Warning, TEXT("FIRED"));
				FVector Direction = CursorLocation-CameraLocation;
				Projectile->FireInDirection(Direction.GetSafeNormal(1.0f));
			}
		}
	
	}
// if (World)
// 	{
// 		FActorSpawnParameters SpawnParams;
// 		SpawnParams.Owner = this;
// 		SpawnParams.Instigator = GetInstigator();

// 		// Spawn the projectile at the muzzle.
// 		AEnderProjectile_Normal* Projectile = World->SpawnActor<AEnderProjectile_Normal>(MuzzleLocation, MuzzleRotation, SpawnParams);/*MyEnderProjectileBlueprint*/
// 		if (Projectile)
// 		{
// 			// Set the projectile's initial trajectory.
// 			FVector LaunchDirection = MuzzleRotation.Vector();

// 			Projectile->FireInDirection(LaunchDirection);
			
// 		}
// 	}


}