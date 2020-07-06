// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClickableActor.h"
#include "Enemy.generated.h"

UCLASS()
class DONTDIEPETE_API AEnemy : public AClickableActor
{
	GENERATED_BODY()

private:
	bool shouldMove = true;
	bool isClickable = true;
	

	virtual void Death_Implementation();

	UPROPERTY(EditDefaultsOnly)
	uint32 health = 1;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> hitSounds;

	UFUNCTION()
	void OnHitColorChanged_Elapsed();

	FTimerHandle timerHandle;

	UPROPERTY(EditDefaultsOnly)
	FColor normalColor = FColor(255,255,255,255);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	AEnemy();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float movementSpeed = 20;

	UPROPERTY(EditDefaultsOnly)
		class UPaperFlipbookComponent* flipbook;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* collisionBox;

	UFUNCTION()
	void OnPeteDeath();

	UFUNCTION(BlueprintNativeEvent)
		void Death();

	UPROPERTY(VisibleAnywhere)
	bool isReversed = true;

	virtual void OnClicked() override;
};