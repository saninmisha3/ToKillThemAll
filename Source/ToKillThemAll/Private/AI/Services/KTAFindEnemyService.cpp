// Kill Them All Game, All Rights Reserved


#include "AI/Services/KTAFindEnemyService.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "KTAUtils.h"
#include "Components/KTAAIPerceptionComponent.h"

UKTAFindEnemyService::UKTAFindEnemyService()
{
    NodeName = "Find Emeny";
}

void UKTAFindEnemyService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Blackboard = OwnerComp.GetBlackboardComponent();
    if (Blackboard)
    {
        const auto Controller = OwnerComp.GetAIOwner();
        const auto PerceptionComponent = KTAUtils::GetKTAPlayerComponent<UKTAAIPerceptionComponent>(Controller);
        if (PerceptionComponent)
        {
            Blackboard->SetValueAsObject(EnemyActorKey.SelectedKeyName, PerceptionComponent->GetClosesEnemy());
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}
