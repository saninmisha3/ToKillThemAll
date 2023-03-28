// Kill Them All Game, All Rights Reserved

#include "AI/Decorators/KTANeedAmmoDecorator.h"
#include "AIController.h"
#include "Components/KTAWeaponComponent.h"
#include "KTAUtils.h"


UKTANeedAmmoDecorator::UKTANeedAmmoDecorator()
{
    NodeName = "Need Ammo";
}

bool UKTANeedAmmoDecorator::CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (!Controller)
        return false;

    const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(Controller->GetPawn());
    if (!WeaponComponent)
        return false;
    

    return WeaponComponent->NeedAmmo(WeaponType);
}
