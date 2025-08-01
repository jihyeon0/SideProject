// Copyright Epic Games, Inc. All Rights Reserved.

#include "SideProjectGameMode.h"
#include "SideProjectCharacter.h"
#include "UObject/ConstructorHelpers.h"

ASideProjectGameMode::ASideProjectGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
