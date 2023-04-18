// Kill Them All Game, All Rights Reserved


#include "UI/KTASpectatorWidget.h"
#include "Components/KTARespawnComponent.h"
#include "KTAUtils.h"

bool UKTASpectatorWidget::GetRespawnTime(int32 &CountDownTime) const
{
    const auto RespawnComponent = KTAUtils::GetKTAPlayerComponent<UKTARespawnComponent>(GetOwningPlayer());
    if (!RespawnComponent || !RespawnComponent->IsRespawnInProgress())
    return false;

    CountDownTime = RespawnComponent->GetRespawnCountDown();
    return true;
}
