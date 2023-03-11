// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "KTABaseCharacter.h"
#include "KTAAICharacter.generated.h"

class UBehaviorTree;
    /**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAAICharacter : public AKTABaseCharacter
{
    GENERATED_BODY()

  public:
    AKTAAICharacter(const FObjectInitializer &ObjInit);
    
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    UBehaviorTree *BehaviorTreeAsset;

    protected:
    virtual void OnDeath() override;
};
