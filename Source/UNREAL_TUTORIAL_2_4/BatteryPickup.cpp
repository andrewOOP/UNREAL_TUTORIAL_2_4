// Fill out your copyright notice in the Description page of Project Settings.

#include "BatteryPickup.h"
#include "UNREAL_TUTORIAL_2_4.h"

//Set default values
ABatteryPickup::ABatteryPickup()
{
	GetMesh()->SetSimulatePhysics(true);

	//the base power level of the battery
	BatteryPower = 150.f;
}


void ABatteryPickup::WasCollected_Implementation()
{
	// Use the base pickup behavior
	Super::WasCollected_Implementation();
	// Destroy the battery
	Destroy();
}

// report the power level of the battery
float ABatteryPickup::GetPower()
{
	return BatteryPower;
}