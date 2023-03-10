// Kill Them All Game, All Rights Reserved


#include "Components/KTAAIWeaponComponent.h"
#include "Weapon/KTABaseWeapon.h"


void UKTAAIWeaponComponent::StartFire()
{
    if (!CanFire())
        return;

    if (CurrentWeapon->IsAmmoEmpty())
    {
        NextWeapon();
    }
    else
    {
        CurrentWeapon->StartFire();
    }
}

void UKTAAIWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;

    //UE_LOG(LogTemp, Warning, TEXT("NextW"));

    int32 NextIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    while (NextIndex != CurrentWeaponIndex)
    {
        //UE_LOG(LogTemp, Warning, TEXT("N-%s, C-%s"), NextIndex, CurrentWeaponIndex);

        if (!Weapons[NextIndex]->IsAmmoEmpty())
            break;

        NextIndex = (NextIndex + 1) % Weapons.Num();
    
    
    }
    if (CurrentWeaponIndex != NextIndex)
    {
        CurrentWeaponIndex = NextIndex;
        EquipWeapon(CurrentWeaponIndex);
    }
}
