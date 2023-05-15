// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "KTACoreTypes.h"
#include "KTAGameInstance.generated.h"

class USoundClass;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAGameInstance : public UGameInstance
{
    GENERATED_BODY()

  public:
    void SetStartupLevel(const FLevelData &Level)
    {
        StartupLevel = Level;
    }
    FLevelData GetStartupLevel() const
    {
        return StartupLevel;
    }
    TArray<FLevelData> GetLevelsData() const
    {
        return LevelsData;
    }
    FName GetMenuLevelName() const
    {
        return MenuLevelName;
    }

    void ToggleVolume();

  protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game", meta = (ToolTip = "Level names must be unique"))
    TArray<FLevelData> LevelsData;

    UPROPERTY(EditDefaultsOnly, Category = "Game")
    FName MenuLevelName = NAME_None;

    UPROPERTY(EditDefaultsOnly, Category = "Sound")
    USoundClass *MasterSoundClass;
  private:
    FLevelData StartupLevel;
};
