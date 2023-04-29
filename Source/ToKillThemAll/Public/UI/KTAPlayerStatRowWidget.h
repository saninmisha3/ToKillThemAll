// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTAPlayerStatRowWidget.generated.h"

class UImage;
class UTextBlock;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAPlayerStatRowWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    void SetPlayerName(const FText &Text);
    void SetKills(const FText &Text);
    void SetDeath(const FText &Text);
    void SetTeam(const FText &Text);
    void SetPlayerIndicatorVisibility(bool Visible);

  protected:
    UPROPERTY(meta = (BindWidget))
    UTextBlock *PlayerNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *KillsTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *DeathTextBlock;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *TeamTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage *PlayerIndicatorImage;
};
