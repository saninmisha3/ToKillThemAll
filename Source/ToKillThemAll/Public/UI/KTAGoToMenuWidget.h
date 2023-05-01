// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTAGoToMenuWidget.generated.h"

class UButton;

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAGoToMenuWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *GoToMenuButton;
    virtual void NativeOnInitialized() override;

  private:
    UFUNCTION()
    void OnMenuLevel();
};
