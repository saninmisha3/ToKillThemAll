// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "KTAFireService.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAFireService : public UBTService
{
	GENERATED_BODY()

		public:
    UKTAFireService();

	protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
      FBlackboardKeySelector EnemyActorKey;

	virtual void TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds) override;
	
};
