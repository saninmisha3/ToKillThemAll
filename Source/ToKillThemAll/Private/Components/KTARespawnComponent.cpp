// Kill Them All Game, All Rights Reserved

#include "Components/KTARespawnComponent.h"
#include "KTAGameModeBase.h"


UKTARespawnComponent::UKTARespawnComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UKTARespawnComponent::Respawn(int32 RespawnTime)
{
    if (!GetWorld())
        return;

    RespawnCountDown = RespawnTime;
    GetWorld()->GetTimerManager().SetTimer(RespawnTimerHandle, this, &UKTARespawnComponent::RespawnTimerUpdate, 1.0f, true);
}

bool UKTARespawnComponent::IsRespawnInProgress() const
{
    return GetWorld() && GetWorld()->GetTimerManager().IsTimerActive(RespawnTimerHandle);
}

void UKTARespawnComponent::RespawnTimerUpdate()
{
    if (--RespawnCountDown <= 0)
    {
        if (!GetWorld())
        return;
        GetWorld()->GetTimerManager().ClearTimer(RespawnTimerHandle);

         const auto GameMode = Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode());
        if (!GameMode)
            return;

        GameMode->RespawnRequest(Cast<AController>(GetOwner()));
    }
}

