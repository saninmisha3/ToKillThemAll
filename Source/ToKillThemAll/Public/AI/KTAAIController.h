// Kill Them All Game, All Rights Reserved

#pragma once

#include "AIController.h"
#include "CoreMinimal.h"
#include "KTAAIController.generated.h"

class UKTAAIPerceptionComponent;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAAIController : public AAIController
{
    GENERATED_BODY()

  public:
    AKTAAIController();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKTAAIPerceptionComponent *KTAAIPerceptionComponent;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName FocusOnKeyName = "EnemyActor";

    virtual void OnPossess(APawn *InPawn) override;
    virtual void Tick(float DeltaTime) override;

    private:
    AActor *GetFocusOnActor() const;
};
