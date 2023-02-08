// Kill Them All Game, All Rights Reserved

#include "Components/KTAHealthComponent.h"
#include "KTAUtils.h"
#include "Pickups/KTAHealthPickup.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthPickup, All, All);



bool AKTAHealthPickup::GivePickupTool(APawn *PlayerPawn)
{
    const auto HealthComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(PlayerPawn);
    if (!HealthComponent)
        return false;

    return HealthComponent->TryToAddHealth(HealthAmount);

    // UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
}
