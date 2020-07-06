// Fill out your copyright notice in the Description page of Project Settings.


#include "Spikes.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PeteGameState.h"
#include "PaperSpriteComponent.h"

// Sets default values
ASpikes::ASpikes()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	SetRootComponent(sprite);

	//create collision box, hook event and size it to 8bit
	collisionBox = CreateDefaultSubobject<UBoxComponent>("Collision");
	collisionBox->SetRelativeLocation(FVector(0, 0, -2));
	collisionBox->SetBoxExtent(FVector(2.f, 1.f, 2.f));
	collisionBox->AttachToComponent(sprite, FAttachmentTransformRules::KeepRelativeTransform);

	//create collision box, hook event and size it to 8bit
	playerCheckBox = CreateDefaultSubobject<UBoxComponent>("playerCheck");
	playerCheckBox->SetRelativeLocation(FVector(0, 0, 0));
	playerCheckBox->SetBoxExtent(FVector(2.f, 1.f, 50.f));
	playerCheckBox->AttachToComponent(sprite, FAttachmentTransformRules::KeepRelativeTransform);
}

// Called when the game starts or when spawned
void ASpikes::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameState<APeteGameState>()->onPeteDeath.AddDynamic(this, &ASpikes::OnPeteDeath);
	playerCheckBox->OnComponentEndOverlap.AddDynamic(this, &ASpikes::OnOverlapEnd);
	movementSpeed = FMath::RandRange(50, 75);
}

// Called every frame
void ASpikes::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (shouldMove)
	{
		FVector previousLocation = GetActorLocation();
		SetActorLocation(FVector(previousLocation.X - (DeltaTime * movementSpeed), previousLocation.Y, previousLocation.Z));
	}
}

void ASpikes::OnPeteDeath()
{
	shouldMove = false;
	isClickable = false;
}

void ASpikes::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	GetWorld()->GetGameState<APeteGameState>()->score++;
}



