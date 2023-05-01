// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAGOverWidget.generated.h"

class UVerticalBox;
class UButton;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAGOverWidget : public UUserWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UVerticalBox *PlayerStatBox;

    UPROPERTY(meta = (BindWidget))
    UButton *ResetLevelButton;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;

    virtual void NativeOnInitialized() override;

  private:
    void OnMatchStateChanged(EKTAMatchState State);
    void UpdatePlayersState();

    UFUNCTION()
    void OnResetLevel();
};
