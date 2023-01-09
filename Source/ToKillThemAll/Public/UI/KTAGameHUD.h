// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KTAGameHUD.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAGameHUD : public AHUD
{
    GENERATED_BODY()

  public:
    virtual void DrawHUD() override;

  private:
    void DrawCrossHaie();
};
