// Kill Them All Game, All Rights Reserved


#include "AI/Services/KTAFireService.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/KTAWeaponComponent.h"
#include "KTAUtils.h"


UKTAFireService::UKTAFireService()
{
    NodeName = "Fire";

}

void UKTAFireService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    const auto Blackboard = OwnerComp.GetBlackboardComponent();

    const auto HasAim = Blackboard && Blackboard->GetValueAsObject(EnemyActorKey.SelectedKeyName);

    if (Controller)
    {
        const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent)
        {
            HasAim ? WeaponComponent->StartFire() : WeaponComponent->StopFire();
        }
    }


    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
