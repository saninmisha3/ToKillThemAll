// Kill Them All Game, All Rights Reserved

#pragma once

#include "BehaviorTree/BTDecorator.h"
#include "CoreMinimal.h"
#include "KTAHealthPercentDecorator.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAHealthPercentDecorator : public UBTDecorator
{
    GENERATED_BODY()
  public:
    UKTAHealthPercentDecorator();

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    float HealthPercent = 0.60f;
    virtual bool CalculateRawConditionValue(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory) const override;
};
