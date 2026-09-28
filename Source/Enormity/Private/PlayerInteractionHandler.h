// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "PlayerInteractionHandler.generated.h"

class APlayerHeadRaycast;

UCLASS(Blueprintable)
class UPlayerInteractionHandler : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UPlayerInteractionHandler();

	UFUNCTION()
	void StartHover(AActor* hitActor);
	
	UFUNCTION()
	void WhileHover(AActor* hitActor);
	
	UFUNCTION()
	void EndHover(AActor* hitActor);	
	bool isHover = false;

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void StartInteract();

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void WhileInteract();

	UFUNCTION(BlueprintCallable, Category = Interaction)
	void EndInteract();
	bool isInteract = false;

	void Scroll(float scrollDist);

	UPROPERTY()
	float InteractDist;

	UPROPERTY()
	float ObjectDist;

	UPROPERTY(BlueprintReadOnly)
	float MaxInteractDist;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	APlayerHeadRaycast* playerRaycast;

	AActor* hoverObject;
	AActor* interactObject;

	FVector* hitPosition;
	FVector* hitNormal;

	void SetActorOutlineStencil(AActor* highlightActor, int stencilVal);

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};


