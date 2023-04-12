// Kill Them All Game, All Rights Reserved

#include "UI/KTAGameDataWidget.h"
#include "Player/KTAPlayerState.h"
#include "KTAGameModeBase.h"


int32 UKTAGameDataWidget::GetRoundCountDown() const
{
    const auto GameMode = GetKTAGameMode();
    return GameMode ? GameMode->GetRoundCountDown() : 0;
}

int32 UKTAGameDataWidget::GetCurrentRound() const
{
    const auto GameMode = GetKTAGameMode();
    return GameMode ? GameMode->GetCurrentRound() : 0;
}

int32 UKTAGameDataWidget::GetKillsNum() const
{
    const auto PlayerState = GetKTAPlayerState();
    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

AKTAGameModeBase *UKTAGameDataWidget::GetKTAGameMode() const
{
    return GetWorld() ? Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode()) : nullptr;
}

AKTAPlayerState *UKTAGameDataWidget::GetKTAPlayerState() const
{
    return GetOwningPlayer() ? Cast<AKTAPlayerState>(GetOwningPlayer()->PlayerState) : nullptr;
}

bool UKTAGameDataWidget::GetCurrentGameData(FGameData &GmData) const
{
    const auto GameMode = GetKTAGameMode();

    if (!GameMode)
        return false;

    GmData = GameMode->GetCurrentGameData();
        return true;
}
