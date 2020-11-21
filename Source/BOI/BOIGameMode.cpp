// Copyright Epic Games, Inc. All Rights Reserved.

#include "BOIGameMode.h"
#include "BOIPlayerController.h"
#include "BOICharacter.h"
#include "UObject/ConstructorHelpers.h"

ABOIGameMode::ABOIGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ABOIPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}