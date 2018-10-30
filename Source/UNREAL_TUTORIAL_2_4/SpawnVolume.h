// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "Components/BoxComponent.h"
#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SpawnVolume.generated.h"

UCLASS()
class UNREAL_TUTORIAL_2_4_API ASpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnVolume();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Box component to specify where to spawn stuff
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Spawning")
	UBoxComponent* WhereToSpawn;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	//Returns the spawn box component
	FORCEINLINE UBoxComponent* GetWhereToSpawn() { return WhereToSpawn; }
	
	//Find a random point in the spawn volume
	UFUNCTION(BlueprintPure, Category="Spawning")
	FVector GetRandomPointInVolume();
};
