// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DebugObject.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI, Blueprintable)
class UDebugObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ENORMITY_API IDebugObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Debug)
	void DebugStart();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Debug)
	void DebugTick();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Debug)
	void DebugConditional();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent, Category = Debug)
	bool isDebug(); public:
};
