
#include "DebugHandler.h"

#include "DebugObject.h"

#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"

void UDebugHandler::Initialize(FSubsystemCollectionBase& Collection) {
	Super::Initialize(Collection);
}

void UDebugHandler::OnWorldBeginPlay(UWorld& InWorld) {
	Super::OnWorldBeginPlay(InWorld);

	currentWorld = GetWorld();

	if (currentWorld) {
		gatherDebugObjects(currentWorld, currentWorld->GetGameInstance());
		globalInitDebug();
	}
}

void UDebugHandler::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);

	if (currentWorld) {
		globalTickDebug(DeltaTime);
	}
}

TStatId UDebugHandler::GetStatId() const {
	RETURN_QUICK_DECLARE_CYCLE_STAT(UDebugHandler, STATGROUP_Tickables);
}

bool UDebugHandler::DoesSupportWorldType(const EWorldType::Type WorldType) const {
	return WorldType == EWorldType::Game || WorldType == EWorldType::PIE;
}

void UDebugHandler::gatherDebugObjects(UWorld* world, UGameInstance* gameInstance) {

	for (UGameInstanceSubsystem* subsystem : gameInstance->GetSubsystemArrayCopy<UGameInstanceSubsystem>()) {
		if (!IsValid(subsystem)) continue;

		if (subsystem->Implements<UDebugObject>()) {
			if (IDebugObject::Execute_isDebug(subsystem)) {
				DebugSubsystems.Emplace(subsystem);
			}
		}
	}

	for (TActorIterator<AActor> It(world); It; ++It) {
		AActor* actor = *It;
		if (!IsValid(actor)) continue;

		if (actor->GetClass()->ImplementsInterface(UDebugObject::StaticClass())) {
			if (IDebugObject::Execute_isDebug(actor)) {
				DebugActors.Emplace(actor);
			}
		}
	}

	for (TObjectIterator<UActorComponent> It; It; ++It) {
		UActorComponent* comp = *It;
		if (!IsValid(comp)) continue;

		if (comp->GetClass()->ImplementsInterface(UDebugObject::StaticClass())) {
			if (IDebugObject::Execute_isDebug(comp)) {
				DebugComponents.Emplace(comp);
			}
		}
	}
}

void UDebugHandler::globalInitDebug() {
	for (UGameInstanceSubsystem* debugSubsystem : DebugSubsystems) {
		IDebugObject::Execute_DebugStart(debugSubsystem);
	}

	for (AActor* debugActor : DebugActors) {
		IDebugObject::Execute_DebugStart(debugActor);
	}

	for (UActorComponent* debugComponent : DebugComponents) {
		IDebugObject::Execute_DebugStart(debugComponent);
	}
}

void UDebugHandler::globalTickDebug(float DeltaTime) {
	for (UGameInstanceSubsystem* debugSubsystem : DebugSubsystems) {
		IDebugObject::Execute_DebugTick(debugSubsystem);
	}
	for (AActor* debugActor : DebugActors) {
		IDebugObject::Execute_DebugTick(debugActor);
	}

	for (UActorComponent* debugComponent : DebugComponents) {
		IDebugObject::Execute_DebugTick(debugComponent);
	}
}

void UDebugHandler::objectDebug(UObject* debugObject) {
	if (debugObject && debugObject->Implements<UDebugObject>()) {
		IDebugObject::Execute_DebugConditional(debugObject);
	}
}