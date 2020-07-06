// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ClickingPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class DONTDIEPETE_API AClickingPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void LineTraceForClickableObject();
};
