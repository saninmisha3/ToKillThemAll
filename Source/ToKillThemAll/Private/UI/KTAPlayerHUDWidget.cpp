// Kill Them All Game, All Rights Reserved

#include "UI/KTAPlayerHUDWidget.h"
#include "Components/KTAHealthComponent.h"
#include "Components/KTAWeaponComponent.h"
#include "KTAUtils.h"
#include "Components/ProgressBar.h"
#include "Player/KTAPlayerState.h"

void UKTAPlayerHUDWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (GetOwningPlayer())
    {
        GetOwningPlayer()->GetOnNewPawnNotifier().AddUObject(this, &UKTAPlayerHUDWidget::OnNewPawn);
        OnNewPawn(GetOwningPlayerPawn());
    }
   
}

void UKTAPlayerHUDWidget::OnHealthChanged(float Health, float HealthDelta)
{
    if (HealthDelta < 0.0f)
    {
        OnTakeDamage();

        if (!IsAnimationPlaying(DamageAnimation))
        {
            PlayAnimation(DamageAnimation);
        }
    }
    

    UpdateHealthBar();
}

void UKTAPlayerHUDWidget::OnNewPawn(APawn *NewPawn)
{

    const auto HeathComponent = KTAUtils::GetKTAPlayerComponent<UKTAHealthComponent>(NewPawn);
    
    if (HeathComponent && !HeathComponent->OnHealthChanged.IsBoundToObject(this))
    {
        HeathComponent->OnHealthChanged.AddUObject(this, &UKTAPlayerHUDWidget::OnHealthChanged);
    }
    UpdateHealthBar();
}

void UKTAPlayerHUDWidget::UpdateHealthBar()
{
    if(HealthProgressBar)
    {
        HealthProgressBar->SetFillColorAndOpacity(Get_HealthPercent() > PercentColorThreshold ? GoodColor : BadColor);
    }
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

int32 UKTAPlayerHUDWidget::GetKillsNum() const
{
    const auto Controller = GetOwningPlayer();
    if (!Controller)
        return 0;

    const auto PlayerState = Cast<AKTAPlayerState>(GetOwningPlayer()->PlayerState);

    return PlayerState ? PlayerState->GetKillsNum() : 0;
}

FString UKTAPlayerHUDWidget::FormatBullets(int32 BulletsNum) const
{
    const int32 MaxLen = 3;
    const TCHAR PrefixSymbol = '0';

    auto BulletSTR = FString::FromInt(BulletsNum);
    const auto SymbolNumToAdd = MaxLen - BulletSTR.Len();

    if (SymbolNumToAdd > 0)
    {
        BulletSTR = FString::ChrN(SymbolNumToAdd, PrefixSymbol).Append(BulletSTR);
    }

    return BulletSTR;
}
