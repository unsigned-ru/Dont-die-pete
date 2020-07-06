// Fill out your copyright notice in the Description page of Project Settings.


#include "ClickingPlayerController.h"
#include "ClickableActor.h"

void AClickingPlayerController::LineTraceForClickableObject() 
{
	//Get world direction & location mouse position
	FVector worldLocation;
	FVector worldDirection;
	DeprojectMousePositionToWorld(worldLocation, worldDirection);

	//Line trace and scan for hit objects
	FHitResult traceResult;
	float distance = 100.f;
	FVector endLocation = worldLocation + (distance * worldDirection);

	//perform line trace in if-statement, if nothing is hit don't continue.
	if (!GetWorld()->LineTraceSingleByChannel(traceResult, worldLocation, endLocation, ECollisionChannel::ECC_Visibility)) return;
	
	if (AClickableActor* clickableActor = Cast<AClickableActor>(traceResult.GetActor()))
		clickableActor->OnClicked();
}