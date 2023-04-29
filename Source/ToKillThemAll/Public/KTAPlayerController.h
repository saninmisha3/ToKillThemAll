// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "GameFramework/PlayerController.h"
#include "KTAPlayerController.generated.h"


class UKTARespawnComponent;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAPlayerController : public APlayerController
{
    GENERATED_BODY()
  public:
    AKTAPlayerController();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKTARespawnComponent *RespawnComponent;

    virtual void BeginPlay() override;
    virtual void SetupInputComponent() override;

  private:
    void OnPauseDame();
    void OnMatchStateChanged(EKTAMatchState State);
};
