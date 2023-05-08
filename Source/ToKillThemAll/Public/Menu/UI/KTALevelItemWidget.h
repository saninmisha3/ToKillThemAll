// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTALevelItemWidget.generated.h"

class UButton;
class UTextBlock;
class UImage;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTALevelItemWidget : public UUserWidget
{
    GENERATED_BODY()
  public:
    FOnLevelSelectedSignature OnLevelSelected;

    void SetLevelData(const FLevelData &Data);
    FLevelData GetLevelData() const
    {
        return LevelData;
    }
    void SetSelected(bool IsSelected);

  protected:
    UPROPERTY(meta = (BindWidget))
    UButton *LevelSelectButton;

    UPROPERTY(meta = (BindWidget))
    UTextBlock *LevelNameTextBlock;

    UPROPERTY(meta = (BindWidget))
    UImage *LevelImage = nullptr;

    UPROPERTY(meta = (BindWidget))
    UImage *FrameImage = nullptr;

    virtual void NativeOnInitialized() override;

  private:
    FLevelData LevelData;

    UFUNCTION()
    void OnLevelitemClicked();

    UFUNCTION()
    void OnLevelItemHovered();

    UFUNCTION()
    void OnLevelItemUpHovered();
};
