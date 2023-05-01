// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KTAMenuHUD.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAMenuHUD : public AHUD
{
    GENERATED_BODY()

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> MenuWidgetClass;

    virtual void BeginPlay() override;
};
