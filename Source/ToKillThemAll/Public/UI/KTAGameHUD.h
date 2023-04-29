// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "KTACoreTypes.h"
#include "KTAGameModeBase.h"
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

  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PlayerHUDWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> PauseWidgetClass;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    TSubclassOf<UUserWidget> GameOverWidgetClass;

    virtual void BeginPlay() override;

  private:
    UPROPERTY()
    TMap<EKTAMatchState, UUserWidget *> GameWidgets;


    UPROPERTY()
    UUserWidget *CurrentWinget = nullptr;

        void DrawCrossHaie();
    void OnMatchStateChanged(EKTAMatchState State);
};
