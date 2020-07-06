// Fill out your copyright notice in the Description page of Project Settings.


#include "Bomb.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PeteGameState.h"
#include "PaperSpriteComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ABomb::ABomb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sprite = CreateDefaultSubobject<UPaperSpriteComponent>("Sprite");
	SetRootComponent(sprite);

	flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	flipbook->SetLooping(false);
	flipbook->Stop();
	flipbook->SetSpriteColor(FColor(0, 0, 0, 0));
	flipbook->SetRelativeLocation(FVector(0, 0, 0));
	flipbook->AttachToComponent(sprite, FAttachmentTransformRules::KeepRelativeTransform);
	
	//create collision box, hook event and size it to 8bit
	collisionBox = CreateDefaultSubobject<UBoxComponent>("Collision");
	collisionBox->SetRelativeLocation(FVector(0, 0, 0));
	collisionBox->SetBoxExtent(FVector(4.f, 1.f, 4.f));
	collisionBox->OnComponentBeginOverlap.AddDynamic(this, &ABomb::OnOverlap);
	collisionBox->AttachToComponent(sprite, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ABomb::BeginPlay()
{
	Super::BeginPlay();
	GetWorld()->GetGameState<APeteGameState>()->onPeteDeath.AddDynamic(this, &ABomb::OnPeteDeath);
	
	movementSpeed = FMath::RandRange(15, 35);
}

// Called every frame
void ABomb::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (shouldMove)
	{
		FVector previousLocation = GetActorLocation();
		SetActorLocation(FVector(previousLocation.X - (DeltaTime * movementSpeed), previousLocation.Y, previousLocation.Z));
	}
}

void ABomb::OnClicked()
{
	Super::OnClicked();

	if (!isClickable) return;

	sprite->SetSpriteColor(FColor(0, 0, 0, 0));
	flipbook->PlayFromStart();
	flipbook->SetSpriteColor(FColor(255, 255, 255, 255));

	collisionBox->DestroyComponent();

	GetWorld()->GetGameState<APeteGameState>()->score++;

	UGameplayStatics::PlaySound2D(this, explosionSounds[FMath::RandRange(0, explosionSounds.Num() -1)]);

}

void ABomb::OnOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	sprite->SetSpriteColor(FColor(0, 0, 0, 0));
	flipbook->PlayFromStart();
	flipbook->SetSpriteColor(FColor(255, 255, 255, 255));
}



void ABomb::OnPeteDeath()
{
	shouldMove = false;
	isClickable = false;
}


