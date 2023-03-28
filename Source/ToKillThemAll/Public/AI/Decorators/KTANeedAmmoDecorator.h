// Kill Them All Game, All Rights Reserved

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "KTANeedAmmoDecorator.generated.h"

class AKTABaseWeapon;
    /**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTANeedAmmoDecorator : public UBTDecorator
{
    GENERATED_BODY()
  public:
    UKTANeedAmmoDecorator();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    TSubclassOf<AKTABaseWeapon> WeaponType;

     virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
