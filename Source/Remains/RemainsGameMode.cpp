// Copyright 1998-2017 Epic Games, Inc. All Rights Reserved.

#include "Remains.h"
#include "RemainsGameMode.h"
#include "RemainsHUD.h"
#include "RemainsCharacter.h"

ARemainsGameMode::ARemainsGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/FirstPersonCharacter"));
	//static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPersonCPP/Blueprints/TestFPS_BP.TestFPS_BP"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	// use our custom HUD class
	HUDClass = ARemainsHUD::StaticClass();
}
