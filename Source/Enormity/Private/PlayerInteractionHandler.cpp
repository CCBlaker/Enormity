

#include "PlayerInteractionHandler.h"
#include "Interactable.h"
#include "PlayerHeadRaycast.h"
#include "Kismet/GameplayStatics.h"

UPlayerInteractionHandler::UPlayerInteractionHandler() {
	PrimaryComponentTick.bCanEverTick = true;
}

void UPlayerInteractionHandler::BeginPlay() {
    Super::BeginPlay();

    playerRaycast = Cast<APlayerHeadRaycast>(GetOwner());

    if (playerRaycast) {
        MaxInteractDist = playerRaycast->maxInteractDist;
        playerRaycast->HoverStart.AddDynamic(this, &UPlayerInteractionHandler::StartHover);
        playerRaycast->Hovering.AddDynamic(this, &UPlayerInteractionHandler::WhileHover);
        playerRaycast->HoverEnd.AddDynamic(this, &UPlayerInteractionHandler::EndHover);
    }
}

void UPlayerInteractionHandler::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) {
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

//Hover Event Functions ---------------
void UPlayerInteractionHandler::StartHover(AActor* hoverActor) {
	isHover = true;
	hoverObject = hoverActor;

	if (!hoverObject) { return; }

	if (!isInteract) {
		SetActorOutlineStencil(hoverObject, 1);
	}
}

void UPlayerInteractionHandler::WhileHover(AActor* hitActor) {

}

void UPlayerInteractionHandler::EndHover(AActor* hitActor) {
	isHover = false;

	if (!isInteract) {
		SetActorOutlineStencil(hoverObject, 0);
	}

	hoverObject = nullptr;
}

void UPlayerInteractionHandler::Scroll(float scrollDist) {
	if (isInteract) {
		InteractDist += scrollDist;
		InteractDist = FMath::Clamp(InteractDist, 0.0f, MaxInteractDist);
	}
}

//Interact Event Functions --------------------
void UPlayerInteractionHandler::StartInteract() {
	if (!hoverObject) { return; }

	if (!IInteractable::Execute_IsInteractable(hoverObject)) { return; }

	isInteract = true;
	interactObject = hoverObject;

	InteractDist = playerRaycast->HitInfo.Distance;
	ObjectDist = InteractDist;

	SetActorOutlineStencil(interactObject, 2);

	IInteractable::Execute_StartInteract(interactObject, UGameplayStatics::GetPlayerController(GetWorld(), 0));
}

void UPlayerInteractionHandler::WhileInteract() {
    if (!interactObject || !playerRaycast) { return; }
    
    IInteractable::Execute_WhileInteract(interactObject);

    AActor* CurrentHitActor = playerRaycast->HitInfo.GetActor();
    float CurrentHitDistance = playerRaycast->HitInfo.Distance;

    if (CurrentHitActor) {
        ObjectDist = FMath::Clamp(InteractDist, 0.0f, CurrentHitDistance);
    } else {
        ObjectDist = InteractDist;
    }
}

void UPlayerInteractionHandler::EndInteract() {
	if (!interactObject) { return; }
	isInteract = false;

	if (hoverObject == interactObject) {
		SetActorOutlineStencil(interactObject, 1);
	}
	else {
		SetActorOutlineStencil(interactObject, 0);

		if (hoverObject) {
			SetActorOutlineStencil(hoverObject, 1);
		}
	}
	IInteractable::Execute_EndInteract(interactObject);

	interactObject = nullptr;
}

//Stencil Outline helper function
void UPlayerInteractionHandler::SetActorOutlineStencil(AActor* highlightActor, int stencilVal) {

	TArray<UPrimitiveComponent*> components;
	highlightActor->GetComponents<UPrimitiveComponent>(components);

	for (UPrimitiveComponent* primative : components) {
		primative->SetRenderCustomDepth(true);
		primative->SetCustomDepthStencilValue(stencilVal);
		primative->MarkRenderStateDirty();
	}
}