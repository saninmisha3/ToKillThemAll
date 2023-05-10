// Kill Them All Game, All Rights Reserved

#pragma once

#include "UI/KTABaseWidget.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UKTAGameInstance;
class UKTALevelItemWidget;\
class USoundCue;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAMenuWidget : public UKTABaseWidget
{
    GENERATED_BODY()

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *StartGameButton;

    UPROPERTY(meta = (BindWidget))
    UButton *QuitGameButton;

    UPROPERTY(meta = (BindWidget))
    UHorizontalBox *LevelItemsBox;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> LevelItemWidgetClass;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation *HideAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue* StartgameSound;

    virtual void NativeOnInitialized() override;

    virtual void OnAnimationFinished_Implementation(const UWidgetAnimation *Animation) override;
  private:
    UPROPERTY()
    TArray<UKTALevelItemWidget *> LevelItemWidgets;

    UFUNCTION()
    void OnStartGame();

    UFUNCTION()
    void OnQuitGame();

    void InitLevelItems();
    void OnLevelSelected(const FLevelData& Data);

    UKTAGameInstance *GetKTAGameInstance() const;
};
