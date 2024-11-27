#include "Factory/RControllerFactory.h"
#include "Factory/RControllerBuilder.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogRControllerFactory, Log, All);

URControllerFactory::URControllerFactory(const FObjectInitializer &ObjectInitializer) : Super(ObjectInitializer)
{
  // AActor subclass this ActorFactory creates.
  NewActorClassName = FString("AActor");
  NewActorClass = AActor::StaticClass();
  bDrag = false;
}

// This method causes a static assertion error I found in Unreal Engine 5.5.0
// bool URControllerFactory::CanCreateActorFrom(const FAssetData &AssetData, FText &OutErrorMsg)
// {
//   // Only designed for ControllerAsset Asset.
//   return AssetData.GetClass()->IsChildOf(URControllerDataAsset::StaticClass());
// }

AActor *URControllerFactory::GetDefaultActor(const FAssetData &AssetData)
{
  return NewActorClass->GetDefaultObject<AActor>();
}

// previous SpawnActor signature: https://github.com/urobosim/URoboSim
// AActor *URControllerFactory::SpawnActor(UObject *Asset, ULevel *InLevel, const FTransform &Transform, EObjectFlags InObjectFlags, const FName Name)

// Unreal Engine 5.5.0 function signature API has changed to, but below one causes CoreUObject static assertion error
AActor *URControllerFactory::SpawnActor(UObject *Asset, ULevel *InLevel, const FTransform &Transform, const FActorSpawnParameters &InSpawnParams)
{
  if (bDrag)
  {
    URControllerDataAsset *ControllerDataAsset = CastChecked<URControllerDataAsset>(Asset);
    if (ControllerDataAsset)
    {
      TArray<AActor *> WorldActors;
      UGameplayStatics::GetAllActorsOfClass(InLevel->OwningWorld, ARModel::StaticClass(), WorldActors);

      TArray<ARModel *> Robots;
      for (AActor *&Actor : WorldActors)
      {
        if (ControllerDataAsset->RobotNames.ContainsByPredicate([&](FString RobotName){ return Actor->GetName().Contains(RobotName); }))
        {
          UE_LOG(LogRControllerFactory, Log, TEXT("Found ARModel %s in ControllerDataAsset %s"), *Actor->GetName(), *ControllerDataAsset->GetName())
          Robots.Add(Cast<ARModel>(Actor));
        }
      }
      if (Robots.Num() != 0)
      {
        URControllerBuilder *ControllerBuilder = NewObject<URControllerBuilder>();
        ControllerBuilder->Init(Robots, ControllerDataAsset->ControllerConfiguration);
        ControllerBuilder->Build();
#if WITH_EDITOR
        Robots[0]->GetWorld()->MarkPackageDirty();
#endif // WITH_EDITOR
      }
      else
      {
        for (const FString &RobotName : ControllerDataAsset->RobotNames)
        {
          UE_LOG(LogRControllerFactory, Warning, TEXT("%s not found"), *RobotName)
        }
      }
    }
    else
    {
      UE_LOG(LogRControllerFactory, Error, TEXT("Casting Asset to USDFDataAsset failed"))
    }
  }
  bDrag = !bDrag;
  return nullptr;
}
