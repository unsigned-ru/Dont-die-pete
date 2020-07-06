// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "PeteGameState.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AEnemy::AEnemy()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	flipbook = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook");
	flipbook->SetSpriteColor(normalColor);
	SetRootComponent(flipbook);

	//create collision box, hook event and size it to 8bit
	collisionBox = CreateDefaultSubobject<UBoxComponent>("Collision");
	collisionBox->SetRelativeLocation(FVector(0, 0, 0));
	collisionBox->SetBoxExtent(FVector(4.f, 1.f, 4.f));
	collisionBox->AttachToComponent(flipbook, FAttachmentTransformRules::KeepRelativeTransform);

}

void AEnemy::Death_Implementation()
{
	flipbook->SetSpriteColor(FColor::Red);
}


// Called when the game starts or when spawned
void AEnemy::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorld()->GetGameState<APeteGameState>()->onPeteDeath.AddDynamic(this, &AEnemy::OnPeteDeath);
	movementSpeed = FMath::RandRange(15, 35);
	flipbook->SetSpriteColor(normalColor);
}

// Called every frame
void AEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (shouldMove)
	{
		FVector previousLocation = GetActorLocation();
		if (isReversed) SetActorLocation(FVector(previousLocation.X - (DeltaTime * movementSpeed), previousLocation.Y, previousLocation.Z));
		else SetActorLocation(FVector(previousLocation.X + (DeltaTime * movementSpeed), previousLocation.Y, previousLocation.Z));
	}
		
}

void AEnemy::OnClicked()
{
	Super::OnClicked();
	if (!isClickable) return;

	health--;
	if (health == 0)
	{
		Death();
		collisionBox->DestroyComponent();
		GetWorld()->GetGameState<APeteGameState>()->score++;
	}
	else
	{
		isClickable = false;
		flipbook->SetSpriteColor(FColor(255, 0, 0));

		
		GetWorldTimerManager().SetTimer(timerHandle, this, &AEnemy::OnHitColorChanged_Elapsed, 0.2f, false);
	}
	UGameplayStatics::PlaySound2D(this, hitSounds[FMath::RandRange(0, hitSounds.Num() - 1)]);

}

void AEnemy::OnHitColorChanged_Elapsed()
{
	flipbook->SetSpriteColor(normalColor);
	isClickable = true;
}


void AEnemy::OnPeteDeath()
{
	shouldMove = false;
	isClickable = false;
	flipbook->Stop();
	GetWorldTimerManager().ClearTimer(timerHandle);
}
