// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spawner.generated.h"

UCLASS()
class DONTDIEPETE_API ASpawner : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY(EditAnywhere)
	float difficultyTickRateMin = 5;

	UPROPERTY(EditAnywhere)
	float difficultyTickRateMax = 10;


	UPROPERTY(EditAnywhere)
	float startSpawnRate = 6;

	UPROPERTY(EditAnywhere)
	float minSpawnRate = 1;

	UPROPERTY(EditAnywhere)
	float maxSpawnRateOffset = 2;

	UPROPERTY(EditAnywhere)
	float decrement = 0.25f;

	UPROPERTY(EditAnywhere)
	bool isReversed = false;

	float currentSpawnRate;

	UPROPERTY(EditInstanceOnly)
	TArray<TSubclassOf<AActor>> spawnBlueprints;

	UFUNCTION()
	void OnSpawnTimer_Elapsed();

	UFUNCTION()
	void OnDifficultyTimer_Elapsed();

	FTimerHandle spawnTimerHandle;
	FTimerHandle difficultyTimerHandle;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ASpawner();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnPeteDeath();
};
