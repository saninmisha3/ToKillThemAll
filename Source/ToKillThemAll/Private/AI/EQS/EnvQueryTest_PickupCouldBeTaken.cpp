// Kill Them All Game, All Rights Reserved


#include "AI/EQS/EnvQueryTest_PickupCouldBeTaken.h"
#include "EnvironmentQuery/Items/EnvQueryItemType_ActorBase.h"
#include "Pickups/KTABasePickup.h"

 UEnvQueryTest_PickupCouldBeTaken::UEnvQueryTest_PickupCouldBeTaken(const FObjectInitializer &ObjectInitializer)//
    : Super(ObjectInitializer)
{
     Cost = EEnvTestCost::Low;
     ValidItemType = UEnvQueryItemType_ActorBase::StaticClass();
     SetWorkOnFloatValues(false);
 }

 void UEnvQueryTest_PickupCouldBeTaken::RunTest(FEnvQueryInstance &QueryInstance) const
{
     const auto DataOwner = QueryInstance.Owner.Get();
     BoolValue.BindData(DataOwner, QueryInstance.QueryID);
     const auto WantsBeTakeble = BoolValue.GetValue();

     for (FEnvQueryInstance::ItemIterator It(this, QueryInstance); It; ++It)
     {
         const auto ItemActor = GetItemActor(QueryInstance, It.GetIndex());
         const auto PickupActor = Cast<AKTABasePickup>(ItemActor);

         if (!PickupActor)
             continue;

         const auto CouldBeTaking = PickupActor->CouldBeTaking();
         It.SetScore(TestPurpose, FilterType, CouldBeTaking, WantsBeTakeble);
     }
 }