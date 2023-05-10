// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTABaseWidget.generated.h"

class USoundCue;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTABaseWidget : public UUserWidget
{
    GENERATED_BODY()
  public:
    void Show();

  protected:
    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation *ShowAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue *OpenSound;
};
