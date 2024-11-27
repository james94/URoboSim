// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

// #include "UnrealEd.h"
#include "SDF/SDFDataAsset.h"
#include "ActorFactories/ActorFactory.h"
#include "RControllerFactory.generated.h"

/**
 * Own ActorFactory which creates a robot from SDFData Asset.
 */
UCLASS()
class UROBOSIMEDITOR_API URControllerFactory : public UActorFactory
{
    GENERATED_BODY()

private:
    URControllerFactory(const FObjectInitializer& ObjectInitializer);

    /**
     * Checks if AssetData is intended for the factory.
     * Checks if an RRobot can be built by AssetData.
     */
    // This method causes a static assertion error I found in Unreal Engine 5.5.0
    // virtual bool CanCreateActorFrom(const FAssetData& AssetData, FText& OutErrorMsg) override;

    /** Initialize NewActorClass if necessary, and return default actor for that class. */
    virtual AActor* GetDefaultActor(const FAssetData& AssetData) override;

    /** Spawns the robot */
    // previous SpawnActor signature: https://github.com/urobosim/URoboSim
    // virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, EObjectFlags ObjectFlags, const FName Name) override;
    
    // Unreal Engine 5.5.0 function signature API has changed to, but below one causes CoreUObject static assertion error
    virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;

    bool bDrag;
};
