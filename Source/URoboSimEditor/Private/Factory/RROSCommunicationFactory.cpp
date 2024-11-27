// Fill out your copyright notice in the Description page of Project Settings.


#include "Factory/RROSCommunicationFactory.h"
#include "Factory/RROSCommunicationBuilder.h"
#include "Kismet/GameplayStatics.h"

URROSCommunicationFactory::URROSCommunicationFactory(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
  // AActor subclass this ActorFactory creates.
  NewActorClassName = FString("AActor");
  NewActorClass = AActor::StaticClass();
  bDrag = false;
}

// This method causes a static assertion error I found in Unreal Engine 5.5.0
// bool URROSCommunicationFactory::CanCreateActorFrom(const FAssetData &AssetData, FText &OutErrorMsg)
// {
//   // Only designed for ControllerAsset Asset.
//   return AssetData.GetClass()->IsChildOf(URROSCommunicationDataAsset::StaticClass());
// }

AActor *URROSCommunicationFactory::GetDefaultActor(const FAssetData &AssetData)
{
  return NewActorClass->GetDefaultObject<AActor>();
}

// Unreal Engine 5.5.0 function signature API has changed to, but below one causes CoreUObject static assertion error
AActor* URROSCommunicationFactory::SpawnActor(UObject* Asset, ULevel* InLevel, const FTransform& Transform, const FActorSpawnParameters& InSpawnParams)
{
  if (bDrag)
  {
    URROSCommunicationDataAsset *ROSCommunicationDataAsset = CastChecked<URROSCommunicationDataAsset>(Asset);
    if (ROSCommunicationDataAsset)
    {
      TArray<AActor *> WorldActors;
      UGameplayStatics::GetAllActorsOfClass(InLevel->OwningWorld, ARModel::StaticClass(), WorldActors);

      for (auto &Actor : WorldActors)
      {
        UE_LOG(LogTemp, Error, TEXT("Found Model %s"), *Actor->GetName());
        if (Actor->GetName().Contains(ROSCommunicationDataAsset->RobotName))
        {
          UE_LOG(LogTemp, Error, TEXT("Robot found"));
          ARModel *Robot = Cast<ARModel>(Actor);
          URROSCommunicationBuilder *ROSCommunicationBuilder = NewObject<URROSCommunicationBuilder>();
          ROSCommunicationBuilder->Init(Robot, ROSCommunicationDataAsset->ROSCommunicationConfiguration);
          ROSCommunicationBuilder->Build(ROSCommunicationDataAsset->PublisherConfiguration,
                                         ROSCommunicationDataAsset->SubscriberConfiguration,
                                         ROSCommunicationDataAsset->ServiceServerConfiguration,
                                         ROSCommunicationDataAsset->ServiceClientConfiguration,
                                         ROSCommunicationDataAsset->ActionServerConfiguration);

#if WITH_EDITOR
        Robot->GetWorld()->MarkPackageDirty();
#endif // WITH_EDITOR
        }
      }
    }
    else
    {
      UE_LOG(LogTemp, Error, TEXT("Asset cast to USDFDataAsset failed"));
    }
  }
  else
  {
    bDrag = !bDrag;
  }

  // Creates RRobot Actor.
  return nullptr;
}
