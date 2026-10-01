#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "DebugHandler.generated.h"

UCLASS()
class ENORMITY_API UDebugHandler : public UTickableWorldSubsystem
{
	GENERATED_BODY()

public:
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void OnWorldBeginPlay(UWorld& InWorld) override;
	virtual void Tick(float DeltaTime) override;

	virtual TStatId GetStatId() const override;
	virtual bool DoesSupportWorldType(const EWorldType::Type WorldType) const override;
	
	// CRITICAL: Tells the engine it is allowed to tick during PIE / Game frames
	virtual ETickableTickType GetTickableTickType() const override { return ETickableTickType::Always; }

	void gatherDebugObjects(UWorld* InWorld, UGameInstance* gameInstance);

	UFUNCTION()
	void globalInitDebug();

	UFUNCTION()
	void globalTickDebug(float DeltaTime);

	void objectDebug(UObject* debugObject);

	// FIXED: Protected from GC
	UPROPERTY()
	UWorld* currentWorld;

protected:
	// FIXED: Added UPROPERTY() to prevent tracked elements from dangling/crashing
	UPROPERTY()
	TArray<AActor*> DebugActors;

	UPROPERTY()
	TArray<UActorComponent*> DebugComponents;

	UPROPERTY()
	TArray<UGameInstanceSubsystem*> DebugSubsystems;
};