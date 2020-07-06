// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteComponent.h"
#include "ParallaxSpriteComponent2D.generated.h"

/**
 * 
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class DONTDIEPETE_API UParallaxSpriteComponent2D : public UPaperSpriteComponent
{
	GENERATED_BODY()

private:
	UMaterialInstanceDynamic* dynamicMaterial = nullptr;

	UFUNCTION()
		void OnPeteDeath();

protected:
	virtual void BeginPlay() override;

public:
	UParallaxSpriteComponent2D();

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY(EditDefaultsOnly, Category = Variable)
		UMaterialInterface* parallaxMaterial;
	UPROPERTY(EditDefaultsOnly, Category = Variable)
		UTexture* texture;
	UPROPERTY(EditDefaultsOnly, Category = Variable)
		float parallaxSpeed;
	UPROPERTY(EditDefaultsOnly, Category = Variable)
		float parallaxSpeedOnDeath = 0;
};