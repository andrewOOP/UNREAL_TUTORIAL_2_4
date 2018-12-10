// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "UNREAL_TUTORIAL_2_4GameMode.h"
#include "UNREAL_TUTORIAL_2_4Character.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnVolume.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "GameFramework/PawnMovementComponent.h"

AUNREAL_TUTORIAL_2_4GameMode::AUNREAL_TUTORIAL_2_4GameMode()
{
	// set default pawn class to our Blueprinted character
	;
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(*(FPaths::ProjectDir() + "Content/ThirdPersonCPP/Blueprints/ThirdPersonCharacter.uasset"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	//base decay rate
	DecayRate = 0.01f;
}

void AUNREAL_TUTORIAL_2_4GameMode::BeginPlay()
{
	Super::BeginPlay();

	// find all spawn volume Actors
	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnVolume::StaticClass(), FoundActors);

	for (auto Actor : FoundActors)
	{
		ASpawnVolume* SpawnVolumeActor = Cast<ASpawnVolume>(Actor);
		if (SpawnVolumeActor)
		{
			SpawnVolumeActors.AddUnique(SpawnVolumeActor);
		}
	}

	SetCurrentState(EBatteryPlayState::EPlaying);

	AUNREAL_TUTORIAL_2_4Character* MyCharacter = Cast<AUNREAL_TUTORIAL_2_4Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		PowerToWin = (MyCharacter->GetInitialPower())*1.25f;
	}

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);
		if (CurrentWidget != nullptr)
		{
			CurrentWidget->AddToViewport();
		}
	}

	
}

void AUNREAL_TUTORIAL_2_4GameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Check that we are using the battery collector character
	AUNREAL_TUTORIAL_2_4Character* MyCharacter = Cast<AUNREAL_TUTORIAL_2_4Character>(UGameplayStatics::GetPlayerPawn(this, 0));
	if (MyCharacter)
	{
		// If our power is greater than needed to win, set the game's state to Won
		if (MyCharacter->GetCurrentPower() > PowerToWin)
		{
			SetCurrentState(EBatteryPlayState::EWon);
		}
		// if the character's power is positive
		else if (MyCharacter->GetCurrentPower() > 0)
		{
			// decrease the character's power using the decay rate
			MyCharacter->UpdatePower(-DeltaTime*DecayRate*(MyCharacter->GetInitialPower()));
		}
		else
		{
			SetCurrentState(EBatteryPlayState::EGameOver);
		}

	}

}

float AUNREAL_TUTORIAL_2_4GameMode::GetPowerToWin() const
{
	return PowerToWin;
}

EBatteryPlayState AUNREAL_TUTORIAL_2_4GameMode::GetCurrentState() const
{
	return CurrentState;
}

void AUNREAL_TUTORIAL_2_4GameMode::SetCurrentState(EBatteryPlayState NewState)
{
	//set current state
	CurrentState = NewState;
	// handle the new current state
	HandleNewState(CurrentState);

}

void AUNREAL_TUTORIAL_2_4GameMode::HandleNewState(EBatteryPlayState NewState)
{
	switch (NewState)
	{
	// If the game is playing
	case EBatteryPlayState::EPlaying:
	{
		// spawn volumes active
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(true);
		}
	}
	break;
	// If we've won the game
	case EBatteryPlayState::EWon:
	{
		// spawn volumes inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
	}
	break;
	// If we've lost the game
	case EBatteryPlayState::EGameOver:
	{
		// spawn volumes inactive
		for (ASpawnVolume* Volume : SpawnVolumeActors)
		{
			Volume->SetSpawningActive(false);
		}
		// block player input
		APlayerController* PlayerController = UGameplayStatics::GetPlayerController(this, 0);
		if (PlayerController)
		{
			PlayerController->SetCinematicMode(true, false, false, true, true);
		}
		// ragdoll the character
		ACharacter* MyCharacter = UGameplayStatics::GetPlayerCharacter(this, 0);
		if (MyCharacter)
		{
			MyCharacter->GetMesh()->SetSimulatePhysics(true);
			MyCharacter->GetMovementComponent()->MovementState.bCanJump = false;
		}
	}
	break;
	// Unknown/default state
	default:
	case EBatteryPlayState::EUnknown:
	{
		// do nothing
	}
	break;
	}

}