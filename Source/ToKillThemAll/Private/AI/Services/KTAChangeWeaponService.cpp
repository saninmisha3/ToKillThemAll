// Kill Them All Game, All Rights Reserved


#include "AI/Services/KTAChangeWeaponService.h"
#include "Components/KTAWeaponComponent.h"
#include "AIController.h"
#include "KTAUtils.h"

UKTAChangeWeaponService::UKTAChangeWeaponService()
{
    NodeName = "Change Weapon";
}

void UKTAChangeWeaponService::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    const auto Controller = OwnerComp.GetAIOwner();
    if (Controller)
    {
        const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(Controller->GetPawn());
        if (WeaponComponent && Probability > 0 && FMath::FRand() <= Probability)
        {
            WeaponComponent->NextWeapon();
        }
    }
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
}