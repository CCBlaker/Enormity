// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerHeadRaycast.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FHover, AActor*, HoverActor);

UCLASS(ClassGroup = (PlayerComponents), meta = (BlueprintSpawnableComponent))
class APlayerHeadRaycast : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APlayerHeadRaycast();

	UPROPERTY(BlueprintReadOnly)
	FVector headPos;

	UPROPERTY(BlueprintReadOnly)
	FRotator headRot;

	UPROPERTY(EditAnywhere)
	float maxInteractDist = 200.0f;

	UPROPERTY(BlueprintReadOnly)
	FHitResult HitInfo;

	AActor* HitActor;
	AActor* HoverActor;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FHover HoverStart;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FHover Hovering;

	UPROPERTY(BlueprintAssignable, Category = "Interaction")
	FHover HoverEnd;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	bool persistLines = false;
	float lifeTime = 0.0;
	uint8 depthPriority = 0;
	float lineThickness = 1.0;

	void LineTraceIntersect();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable)
	void RaycastHover(float DeltaTime);

	FCollisionQueryParams RaycastParams;
};