// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAMenuWidget.generated.h"

class UButton;
class UHorizontalBox;
class UKTAGameInstance;
class UKTALevelItemWidget;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAMenuWidget : public UUserWidget
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

    virtual void NativeOnInitialized() override;

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
