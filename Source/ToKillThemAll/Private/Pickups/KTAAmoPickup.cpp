// Kill Them All Game, All Rights Reserved

#include "Components/KTAHealthComponent.h"
#include "Components/KTAWeaponComponent.h"
#include "KTAUtils.h"
#include "Pickups/KTAAmoPickup.h"


DEFINE_LOG_CATEGORY_STATIC(LogAmmoPickup, All, All);

bool AKTAAmoPickup::GivePickupTool(APawn *PlayerPawn)
{
    const auto HealthComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(PlayerPawn);
    if (!HealthComponent || HealthComponent->IsDead())
        return false;

    const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(PlayerPawn);
    if (!WeaponComponent)
        return false;

    return WeaponComponent->TryToAddAmmo(WeaponType, ClipsAmount);


    //UE_LOG(LogAmmoPickup, Display, TEXT("Ammo was taken"));
    
}