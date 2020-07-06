// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClickableActor.generated.h"

UCLASS()
class DONTDIEPETE_API AClickableActor : public AActor
{
	GENERATED_BODY()
	
private:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AClickableActor();
	// Called every frame
	/*virtual void Tick(float DeltaTime) override;*/

	virtual void OnClicked();
	

};
