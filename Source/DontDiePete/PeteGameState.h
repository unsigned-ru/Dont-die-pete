// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "PeteGameState.generated.h"

/**
 * 
 */
UCLASS()
class DONTDIEPETE_API APeteGameState : public AGameStateBase
{
	GENERATED_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnPeteDeath);

	UFUNCTION()
	void OnPeteDeath_Execute();

protected:
	virtual void BeginPlay() override;

public:
	UPROPERTY(BlueprintAssignable)
	FOnPeteDeath onPeteDeath;

	UPROPERTY(BlueprintReadWrite)
	int score = 0;

	
};
