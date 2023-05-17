// Kill Them All Game, All Rights Reserved

#include "Components/KTAAIPerceptionComponent.h"
#include "AIController.h"
#include "Components/KTAHealthComponent.h"
#include "KTAUtils.h"
#include "Perception/AISense_Sight.h"
#include "Perception/AISense_Damage.h"

AActor *UKTAAIPerceptionComponent::GetClosesEnemy() const
{
    TArray<AActor *> PercieveActors;
    GetCurrentlyPerceivedActors(UAISense_Sight::StaticClass(), PercieveActors);
    if (PercieveActors.Num() == 0)
    {
        GetCurrentlyPerceivedActors(UAISense_Damage::StaticClass(), PercieveActors);
        if (PercieveActors.Num() == 0)
             return nullptr;
    }
       

    const auto Controller = Cast<AAIController>(GetOwner());

    if (!Controller)
        return nullptr;

    const auto Pawn = Controller->GetPawn();
    if (!Pawn)
        return nullptr;

    float BestDistance = MAX_FLT;
    AActor *BestPawn = nullptr;

    for (const auto PercieveActor : PercieveActors)
    {
        const auto HealthComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(PercieveActor);

        const auto PercievePawn = Cast<APawn>(PercieveActor);
        const auto AreEnemies = PercievePawn && KTAUtils::AreEnemies(Controller, PercievePawn->Controller);

        if (HealthComponent && !HealthComponent->IsDead() && AreEnemies) // TODO check if enemies
        {
            const auto CurrentDistance = (PercieveActor->GetActorLocation() - Pawn->GetActorLocation()).Size();
            if (CurrentDistance < BestDistance)
            {
                BestDistance = CurrentDistance;
                BestPawn = PercieveActor;
            }
        }
    }

    return BestPawn;
}