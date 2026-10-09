
#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"	

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

class ENORMITY_API IInteractable
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	void StartInteract(APlayerController* InteractingController);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	void WhileInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	void EndInteract();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Interaction)
	bool IsInteractable();

};
