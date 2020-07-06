// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "PeteGameState.h"
#include "Enemy.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	currentSpawnRate = startSpawnRate;

	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &ASpawner::OnSpawnTimer_Elapsed, currentSpawnRate, true);
	GetWorldTimerManager().SetTimer(difficultyTimerHandle, this, &ASpawner::OnDifficultyTimer_Elapsed, FMath::RandRange(difficultyTickRateMin, difficultyTickRateMax), true);
	GetWorld()->GetGameState<APeteGameState>()->onPeteDeath.AddDynamic(this, &ASpawner::OnPeteDeath);
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ASpawner::OnPeteDeath()
{
	GetWorldTimerManager().ClearTimer(spawnTimerHandle);
	GetWorldTimerManager().ClearTimer(difficultyTimerHandle);
}

void ASpawner::OnSpawnTimer_Elapsed()
{
	FTransform thisTransform = GetActorTransform();
	FActorSpawnParameters spawnParams = FActorSpawnParameters();

	AActor* spawnedActor = GetWorld()->SpawnActor<AActor>(spawnBlueprints[FMath::RandRange(0,spawnBlueprints.Num()-1)], thisTransform);
	if (AEnemy* enemy = Cast<AEnemy>(spawnedActor)) enemy->isReversed = isReversed;

	GetWorldTimerManager().SetTimer(spawnTimerHandle, this, &ASpawner::OnSpawnTimer_Elapsed, currentSpawnRate, true);
}

void ASpawner::OnDifficultyTimer_Elapsed()
{
	float rawRate = currentSpawnRate - decrement;
	currentSpawnRate = FMath::Clamp(FMath::RandRange(rawRate-2, rawRate+2), minSpawnRate, INFINITY);

	GetWorldTimerManager().SetTimer(difficultyTimerHandle, this, &ASpawner::OnDifficultyTimer_Elapsed, FMath::RandRange(difficultyTickRateMin, difficultyTickRateMax), true);
}