// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Spikes.generated.h"

UCLASS()
class DONTDIEPETE_API ASpikes : public AActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditDefaultsOnly)
		class UPaperSpriteComponent* sprite;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* collisionBox;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* playerCheckBox;

	bool shouldMove = true;
	bool isClickable = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ASpikes();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float movementSpeed = 20;

	UFUNCTION()
	void OnPeteDeath();

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
};
