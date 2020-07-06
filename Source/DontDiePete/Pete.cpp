// Fill out your copyright notice in the Description page of Project Settings.


#include "Pete.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PeteGameState.h"
#include "Spikes.h"

// Sets default values
APete::APete()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	SetRootComponent(flipbook);

	collisionBox = CreateDefaultSubobject<UBoxComponent>("Collision");
	collisionBox->SetRelativeLocation(FVector(0, 0, 0));
	collisionBox->SetBoxExtent(FVector(4.f, 1.f, 4.f));
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &APete::OnOverlap);
	collisionBox->AttachToComponent(flipbook, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void APete::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APete::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void APete::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ASpikes>(OtherActor)) return;
	GetWorld()->GetGameState<APeteGameState>()->onPeteDeath.Broadcast();
	flipbook->SetSpriteColor(FColor(255,0,0));
	flipbook->Stop();
}
