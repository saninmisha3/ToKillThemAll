// Kill Them All Game, All Rights Reserved

#include "AI/Decorators/KTAHealthPercentDecorator.h"
#include "AIController.h"
#include "Components/KTAHealthComponent.h"
#include "KTAUtils.h"

UKTAHealthPercentDecorator::UKTAHealthPercentDecorator()
{
    NodeName = "Health Percent";
}

bool UKTAHealthPercentDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto HealthComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(Controller->GetPawn());
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    return HealthComponent->GetHealthPercent() <= HealthPercent;
}
