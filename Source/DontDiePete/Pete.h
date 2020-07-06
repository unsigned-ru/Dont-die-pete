// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Pete.generated.h"

UCLASS()
class DONTDIEPETE_API APete : public APawn
{
	GENERATED_BODY()
	
private:	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	// Sets default values for this actor's properties
	APete();

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
	class UPaperFlipbookComponent* flipbook;
	UPROPERTY(EditDefaultsOnly)
	class UBoxComponent *collisionBox;

	UFUNCTION(BlueprintCallable)
	void OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
