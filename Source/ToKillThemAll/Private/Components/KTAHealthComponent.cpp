// Kill Them All Game, All Rights Reserved

#include "Components/KTAHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "TimerManager.h"

DEFINE_LOG_CATEGORY_STATIC(LogHealthComponent, All, All);

// Sets default values for this component's properties
UKTAHealthComponent::UKTAHealthComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

// Called when the game starts
void UKTAHealthComponent::BeginPlay()
{
    Super::BeginPlay();

    check(MaxHealth > 0);

    SetHealth(MaxHealth);
    // ...

    AActor *ComponentOwner = GetOwner();
    if (ComponentOwner)
    {
        ComponentOwner->OnTakeAnyDamage.AddDynamic(this, &UKTAHealthComponent::OnTakeAnyDamage);
    }
}

void UKTAHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                          AController *InstigatedBy, AActor *DamageCauser)
{

    if (Damage <= 0.0f || IsDead() || !GetWorld())
        return;

    SetHealth(Health - Damage);

    // UE_LOG(LogHealthComponent, Display, TEXT("Damago: %f"), Damage);
    GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);

    if (IsDead())
    {
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UKTAHealthComponent::HealUpdate, HealUpdateTime,
                                               true, HealDelay);
    }
}

void UKTAHealthComponent::HealUpdate()
{
    SetHealth(Health + HealModifier);

    if (IsHeathFull() && GetWorld())
    {
        GetWorld()->GetTimerManager().ClearTimer(HealTimerHandle);
    }
}

void UKTAHealthComponent::SetHealth(float NewHealth)
{
    Health = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    OnHealthChanged.Broadcast(Health);
}

bool UKTAHealthComponent::TryToAddHealth(int32 HealthAmount)
{
    if (IsDead() || IsHeathFull())
        return false;

    SetHealth(Health + HealthAmount);

    return true;
}

bool UKTAHealthComponent::IsHeathFull() const
{
    return FMath::IsNearlyEqual(Health, MaxHealth);
}