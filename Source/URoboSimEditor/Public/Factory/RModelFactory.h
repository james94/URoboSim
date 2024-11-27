// Copyright 2017, Institute for Artificial Intelligence - University of Bremen

#pragma once

// #include "UnrealEd.h"
#include "SDF/SDFDataAsset.h"
#include "ActorFactories/ActorFactory.h"
#include "RModelFactory.generated.h"

class ARModel;
// class SDFAssetData;
// struct FSDFLink;
// struct FSDFJoint;

/**
 * Own ActorFactory which creates a robot from SDFData Asset.
 */
UCLASS()
class UROBOSIMEDITOR_API URModelFactory : public UActorFactory
{
    GENERATED_BODY()

private:
    URModelFactory(const FObjectInitializer& ObjectInitializer);

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

    // TODO (JG): Unreal Engine 5.5.0 function signature API has changed to, but below one causes CoreUObject static assertion error
    virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;


    /** Subclasses may implement this to modify the actor after it has been spawned
        IMPORTANT: If you override this, you should usually also override PostCreateBlueprint()! */
    virtual void PostSpawnActor( UObject* Asset, AActor* NewActor );

    /** Override this in derived factory classes if needed.  This is called after a blueprint is created by this factory to
        update the blueprint's CDO properties with state from the asset for this factory.
        IMPORTANT: If you override this, you should usually also override PostSpawnActor()! */
    virtual void PostCreateBlueprint( UObject* Asset, AActor* CDO );

};
