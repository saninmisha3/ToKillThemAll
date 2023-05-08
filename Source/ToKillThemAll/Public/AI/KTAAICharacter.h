// Kill Them All Game, All Rights Reserved

#pragma once

#include "KTABaseCharacter.h"
#include "CoreMinimal.h"
#include "KTAAICharacter.generated.h"
class UBehaviorTree;
class UWidgetComponent;
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

    virtual void Tick(float DeltaTime) override;

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Components")
    UWidgetComponent *HealthWidgetComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "AI")
    float HealthVisibilityDistance = 1000.0f;

    virtual void BeginPlay() override;

    virtual void OnDeath() override;
    virtual void OnHealthChanged(float Health, float HealthDelta) override;

    private:
    void UpdateHealthWidgetVisibility();

};
