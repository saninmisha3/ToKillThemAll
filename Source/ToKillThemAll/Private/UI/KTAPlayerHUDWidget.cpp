// Kill Them All Game, All Rights Reserved

#include "UI/KTAPlayerHUDWidget.h"
#include "Components/KTAHealthComponent.h"
#include "Components/KTAWeaponComponent.h"
#include "KTAUtils.h"

bool UKTAPlayerHUDWidget::Initialize()
{
    const auto HeathComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(GetOwningPlayerPawn());
    if (HeathComponent)
    {
        HeathComponent->OnHealthChanged.AddUObject(this, &UKTAPlayerHUDWidget::OnHealthChanged);
    }
    return Super::Initialize();
}

void UKTAPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta<0.0f)
    OnTakeDamage();
}

float UKTAPlayerHUDWidget::Get_HealthPercent() const
{
    const auto HeathComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(GetOwningPlayerPawn());

    if (!HeathComponent)
        return 0.0f;

    return HeathComponent->GetHealthPercent();
}

bool UKTAPlayerHUDWidget::GetCurrentWeponUIData(FWeaponUIData &UIData) const
{
    const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeponUIData(UIData);
}

bool UKTAPlayerHUDWidget::GetCurrentWeponAmmoData(FAmmoData &AmmoData) const
{
    const auto WeaponComponent = KTAUtils::GetKTAPlayerComponent<UKTAWeaponComponent>(GetOwningPlayerPawn());
    if (!WeaponComponent)
        return false;

    return WeaponComponent->GetCurrentWeponAmmoData(AmmoData);
}

bool UKTAPlayerHUDWidget::IsPlayerAlive() const
{
    const auto HealthComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(GetOwningPlayerPawn());
    if (!HealthComponent)
        return false;

    return HealthComponent && !HealthComponent->IsDead();
}

bool UKTAPlayerHUDWidget::IsPlayerSpectating() const
{
    const auto Controller = GetOwningPlayer();
    return Controller && Controller->GetStateName() == NAME_Spectating;
}
