// Kill Them All Game, All Rights Reserved

#pragma once

#include "Blueprint/UserWidget.h"
#include "CoreMinimal.h"
#include "KTAGameDataWidget.generated.h"

class AKTAGameModeBase;
class AKTAPlayerState;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAGameDataWidget : public UUserWidget
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentGameData(FGameData &GmData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetRoundCountDown() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetCurrentRound() const;



  private:
    AKTAGameModeBase *GetKTAGameMode() const;
    AKTAPlayerState *GetKTAPlayerState() const;
};
