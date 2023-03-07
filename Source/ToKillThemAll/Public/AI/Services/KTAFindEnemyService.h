// Kill Them All Game, All Rights Reserved

#pragma once

#include "BehaviorTree/BTService.h"
#include "CoreMinimal.h"
#include "KTAFindEnemyService.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAFindEnemyService : public UBTService
{
    GENERATED_BODY()

  public:
    UKTAFindEnemyService();

    protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FBlackboardKeySelector EnemyActorKey;

    virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
};
