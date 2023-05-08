// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTAHealthBarWidget.generated.h"

class UProgressBar;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAHealthBarWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    void SetHealthPercent(float Percent);

  protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar *HealthProgressBar;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentVisibilityThreshold = 0.8f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;
};
