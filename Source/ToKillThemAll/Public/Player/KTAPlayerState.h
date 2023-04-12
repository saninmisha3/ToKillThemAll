// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "KTAPlayerState.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAPlayerState : public APlayerState
{
  GENERATED_BODY()

  public:
    void SetTeamID(int32 ID)
    {
        TeamID = ID;
    }
    int32 GetTeamID() const
    {
        return TeamID;
    }

    void SetTeamColor(FLinearColor Color)
    {
        TeamColor = Color;
    }
    FLinearColor GetTeamColor() const
    {
        return TeamColor;
    }

    void AddKill()
    {
        KillsNum++;
    }
    int32 GetKillsNum() const
    {
        return KillsNum;
    }
    void AddDeath()
    {
        DeathNum++;
    }
    int32 GetDeathNum() const
    {
        return DeathNum;
    }

    void LogInfo();

  private:
    int32 TeamID;
    FLinearColor TeamColor;

    int32 KillsNum = 0;
    int32 DeathNum = 0;
};
