// Kill Them All Game, All Rights Reserved

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "KTAChangeWeaponService.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAChangeWeaponService : public UBTService
{
    GENERATED_BODY()

  public:
    UKTAChangeWeaponService();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI", meta = (ClampMin = "0.0", ClampMax = "1.0"))
    float Probability = 0.5f;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
