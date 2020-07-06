// Fill out your copyright notice in the Description page of Project Settings.


#include "PeteGameState.h"

void APeteGameState::OnPeteDeath_Execute()
{
	UE_LOG(LogTemp, Warning, TEXT("OnPeteDeath Called"));
}

void APeteGameState::BeginPlay()
{
	Super::BeginPlay();
	onPeteDeath.AddDynamic(this, &APeteGameState::OnPeteDeath_Execute);

}
