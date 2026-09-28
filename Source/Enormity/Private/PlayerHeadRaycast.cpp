// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHeadRaycast.h"

#include "DrawDebugHelpers.h"
#include "Interactable.h"

// Sets default values
APlayerHeadRaycast::APlayerHeadRaycast() {
	PrimaryActorTick.bCanEverTick = true;

}

void APlayerHeadRaycast::BeginPlay() {
	Super::BeginPlay();
	
}

void APlayerHeadRaycast::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
}

void APlayerHeadRaycast::LineTraceIntersect() {
	

	FVector startPos = GetActorLocation();
	FVector traceDir = GetActorForwardVector();

	FVector endPos = startPos + (traceDir * maxInteractDist);

	bool Hit = GetWorld()->LineTraceSingleByChannel(
		HitInfo,
		startPos,
		endPos,
		ECC_Visibility,
		RaycastParams
	);

	DrawDebugLine(
		GetWorld(),
		startPos,
		endPos,
		Hit ? FColor::Red : FColor::Green,
		false,
		0.0,
		0,
		1.0
	);
}

void APlayerHeadRaycast::RaycastHover(float DeltaTime)
{
	LineTraceIntersect();

	HitActor = HitInfo.GetActor();
	AActor* newHover = nullptr;

	if (HitActor && HitActor->Implements<UInteractable>()) {
		newHover = HitActor;
	}

	if (HoverActor == newHover) {
		if (!HoverActor) { return; }
		else {
			Hovering.Broadcast(newHover);
		}
	}
	else {
		if (!HoverActor) {
			HoverStart.Broadcast(newHover);
		}
		else if (!newHover) {
			HoverEnd.Broadcast(newHover);
		}
		else {
			HoverEnd.Broadcast(newHover);
			HoverStart.Broadcast(newHover);
		}
	}

	HoverActor = newHover;
}