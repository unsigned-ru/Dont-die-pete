// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ClickableActor.h"
#include "Bomb.generated.h"

UCLASS()
class DONTDIEPETE_API ABomb : public AClickableActor
{
	GENERATED_BODY()
	
private:	
	UPROPERTY(EditDefaultsOnly)
		class UPaperSpriteComponent* sprite;
	UPROPERTY(EditDefaultsOnly)
		class UBoxComponent* collisionBox;

	UPROPERTY(EditDefaultsOnly)
	TArray<USoundBase*> explosionSounds;

	bool shouldMove = true;
	bool isClickable = true;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	ABomb();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	float movementSpeed = 20;

	UFUNCTION()
	void OnPeteDeath();

	virtual void OnClicked() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
		class UPaperFlipbookComponent* flipbook;

	UFUNCTION()
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
