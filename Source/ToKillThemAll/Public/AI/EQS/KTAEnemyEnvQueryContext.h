// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "EnvironmentQuery/EnvQueryContext.h"
#include "KTAEnemyEnvQueryContext.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAEnemyEnvQueryContext : public UEnvQueryContext
{
    GENERATED_BODY()
  public:
    virtual void ProvideContext(FEnvQueryInstance &QueryInstance, FEnvQueryContextData &ContextData) const override;

  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "AI")
    FName EnemyActorKeyName = "EnemyActor";
};
