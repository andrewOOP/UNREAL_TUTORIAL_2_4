// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UNREAL_TUTORIAL_2_4GameMode.h"
#include "UNREAL_TUTORIAL_2_4Character.h"
#include "UObject/ConstructorHelpers.h"

AUNREAL_TUTORIAL_2_4GameMode::AUNREAL_TUTORIAL_2_4GameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPersonCPP/Blueprints/ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
