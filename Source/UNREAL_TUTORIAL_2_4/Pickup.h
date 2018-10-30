// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/Actor.h"
#include "Pickup.generated.h"

UCLASS()
class UNREAL_TUTORIAL_2_4_API APickup : public AActor
{
	GENERATED_BODY()


public:	
	// Sets default values for this actor's properties
	APickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Static mesh for pickup
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Pickup")
	UStaticMeshComponent* PickupMesh;

	//True when pickup can be used
	bool bIsActive;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns mesh for pickup
	FORCEINLINE UStaticMeshComponent* GetMesh() const { return PickupMesh;  }
	
	//Returns if it is active
	UFUNCTION(BlueprintPure, Category="Pickup")
	bool IsActive();

	//Allows others to change active state of pickup
	UFUNCTION(BlueprintCallable, Category="Pickup")
	void SetActive(bool PickupState);
};
