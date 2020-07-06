// Fill out your copyright notice in the Description page of Project Settings.


#include "ParallaxSpriteComponent2D.h"
#include "PeteGameState.h"


UParallaxSpriteComponent2D::UParallaxSpriteComponent2D()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UParallaxSpriteComponent2D::BeginPlay()
{
	Super::BeginPlay();

	dynamicMaterial = CreateDynamicMaterialInstance(0, parallaxMaterial);
	dynamicMaterial->SetTextureParameterValue("Texture", texture);
	
	if (APeteGameState* gameState = GetWorld()->GetGameState<APeteGameState>()) gameState->onPeteDeath.AddDynamic(this, &UParallaxSpriteComponent2D::OnPeteDeath);
}

void UParallaxSpriteComponent2D::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (parallaxSpeed > 0)
	{
		float newOffset = (parallaxSpeed * DeltaTime) + dynamicMaterial->K2_GetScalarParameterValue("Offset");
		dynamicMaterial->SetScalarParameterValue("Offset", newOffset);
	}
}

void UParallaxSpriteComponent2D::OnPeteDeath()
{
	parallaxSpeed = parallaxSpeedOnDeath;
}

