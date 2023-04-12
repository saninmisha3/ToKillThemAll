// Kill Them All Game, All Rights Reserved

#include "Components/KTAHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Pawn.h"
#include "GameFramework/Controller.h"
//#include "Camera/CameraShake.h"
#include "KTAGameModeBase.h"
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
        Killed(InstigatedBy);
        OnDeath.Broadcast();
    }
    else if (AutoHeal && GetWorld())
    {
        GetWorld()->GetTimerManager().SetTimer(HealTimerHandle, this, &UKTAHealthComponent::HealUpdate, HealUpdateTime,
                                               true, HealDelay);
    }
    PlayCameraShake();
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
    const auto NextHealth = FMath::Clamp(NewHealth, 0.0f, MaxHealth);
    const auto HealthDelta = NextHealth - Health;

    Health = NextHealth;
    OnHealthChanged.Broadcast(Health, HealthDelta);
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

void UKTAHealthComponent::PlayCameraShake()
{
    if (IsDead())
        return;

    const auto Player = Cast<APawn>(GetOwner());
    if (!Player)
        return;

    const auto Controller = Player->GetController<APlayerController>();
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    Controller->PlayerCameraManager->StartCameraShake(CamerShake);
}

void UKTAHealthComponent::Killed(AController *KillerController)
{
    if (!GetWorld())
        return;

    const auto GameMode = Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode());

    const auto Player = Cast<APawn>(GetOwner());

    const auto VictingController = Player ? Player->Controller : nullptr;

    GameMode->Killed(KillerController, VictingController);
}
