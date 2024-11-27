// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ActorFactories/ActorFactory.h"
#include "ROSCommunication/RROSCommunicationDataAsset.h"
#include "RROSCommunicationFactory.generated.h"

/**
 * 
 */
UCLASS()
class UROBOSIMEDITOR_API URROSCommunicationFactory : public UActorFactory
{
	GENERATED_BODY()
	
private:
	URROSCommunicationFactory(const FObjectInitializer &ObjectInitializer);

	// This method causes a static assertion error I found in Unreal Engine 5.5.0
	// virtual bool CanCreateActorFrom(const FAssetData &AssetData, FText &OutErrorMsg) override;

	/** Initialize NewActorClass if necessary, and return default actor for that class. */
	virtual AActor *GetDefaultActor(const FAssetData &AssetData) override;

	virtual AActor* SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams) override;

	bool bDrag;
};
