// Kill Them All Game, All Rights Reserved

#include "Components/KTAHealthComponent.h"
#include "Engine/World.h"
#include "GameFramework/Character.h"
#include "GameFramework/Controller.h"
#include "KTAGameModeBase.h"
#include "Perception/AISense_Damage.h"
#include "PhysicalMaterials/PhysicalMaterial.h"
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
        ComponentOwner->OnTakePointDamage.AddDynamic(this, &UKTAHealthComponent::OnTakePointDamage);
        ComponentOwner->OnTakeRadialDamage.AddDynamic(this, &UKTAHealthComponent::OnTakeRadialDamage);
    }
}

void UKTAHealthComponent::OnTakeAnyDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                          AController *InstigatedBy, AActor *DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On any damage: %f"), Damage);
}

void UKTAHealthComponent::OnTakePointDamage(AActor *DamagedActor, float Damage, AController *InstigatedBy,
                                            FVector HitLocation, UPrimitiveComponent *FHitComponent, FName BoneName,
                                            FVector ShotFromDirection, const UDamageType *DamageType,
                                            AActor *DamageCauser)
{
    const auto FinalDamage = Damage * GetPointDamageModifier(DamagedActor, BoneName);
    UE_LOG(LogHealthComponent, Display, TEXT("On point damage: %f, final damage: %f, bones: %s"), Damage, FinalDamage,
           *BoneName.ToString());
    ApplyDamage(FinalDamage, InstigatedBy);
}

void UKTAHealthComponent::OnTakeRadialDamage(AActor *DamagedActor, float Damage, const UDamageType *DamageType,
                                             FVector Origin, FHitResult HitInfo, AController *InstigatedBy,
                                             AActor *DamageCauser)
{
    UE_LOG(LogHealthComponent, Display, TEXT("On radial damage: %f"), Damage);
    ApplyDamage(Damage, InstigatedBy);
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

void UKTAHealthComponent::ApplyDamage(float Damage, AController *InstigatedBy)
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
    ReportDamageEvent(Damage, InstigatedBy);
}

float UKTAHealthComponent::GetPointDamageModifier(AActor *Damaged, const FName &BoneName)
{
    const auto Character = Cast<ACharacter>(Damaged);
    if (!Character ||            //
        !Character->GetMesh() || //
        !Character->GetMesh()->GetBodyInstance(BoneName))
        return 1.0f;

    const auto PhysMaterial = Character->GetMesh()->GetBodyInstance(BoneName)->GetSimplePhysicalMaterial();

    if (!PhysMaterial || !DamageModifiers.Contains(PhysMaterial))
        return 1.0f;

    return DamageModifiers[PhysMaterial];
}

void UKTAHealthComponent::ReportDamageEvent(float Damage, AController *InstigatedBy)
{
    if (!InstigatedBy || !InstigatedBy->GetPawn() || !GetOwner())
        return;
    UAISense_Damage::ReportDamageEvent(GetWorld(),                                  //
                                       GetOwner(),                                  //
                                       InstigatedBy->GetPawn(),                     //
                                       Damage,                                      //
                                       InstigatedBy->GetPawn()->GetActorLocation(), //
                                       GetOwner()->GetActorLocation());
}
