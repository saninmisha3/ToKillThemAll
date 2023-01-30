// Kill Them All Game, All Rights Reserved

#include "Components/KTAWeaponComponent.h"
#include "Animation/KTAEquipFinishedAnimNotify.h"
#include "GameFramework/Character.h"
#include "Weapon/KTABaseWeapon.h"
#include "Animation/KTAReloadFinishedAnimNotify.h"

DEFINE_LOG_CATEGORY_STATIC(LogWeaponComponent, All, All);

// Sets default values for this component's properties
UKTAWeaponComponent::UKTAWeaponComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = false;

    // ...
}

void UKTAWeaponComponent::StartFire()
{
    if (!CanFire())
        return;
    CurrentWeapon->StartFire();
}

void UKTAWeaponComponent::StopFire()
{
    if (!CurrentWeapon)
        return;
    CurrentWeapon->StopFire();
}

// Called when the game starts
void UKTAWeaponComponent::BeginPlay()
{
    Super::BeginPlay();
    CurrentWeaponIndex = 0;

    InitAnimations();
    SpawnWeapons();
    EquipWeapon(CurrentWeaponIndex);
}
void UKTAWeaponComponent::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    CurrentWeapon = nullptr;
    for (auto Weapon : Weapons)
    {
        Weapon->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);
        Weapon->Destroy();
    }
    Weapons.Empty();
    Super::EndPlay(EndPlayReason);
}

void UKTAWeaponComponent::SpawnWeapons()
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || !GetWorld())
        return;

    for (auto OneWeaponData : WeaponData)
    {
        auto Weapon = GetWorld()->SpawnActor<AKTABaseWeapon>(OneWeaponData.WeaponClass);

        if (!Weapon)
            continue;

        Weapon->SetOwner(Character);
        Weapons.Add(Weapon);

        AttachWeaponToSocket(Weapon, Character->GetMesh(), WeaponArmorySocketName);
    }
}

void UKTAWeaponComponent::AttachWeaponToSocket(AKTABaseWeapon *Weapon, USceneComponent *SceneComponent,
                                               const FName &SocketName)
{
    FAttachmentTransformRules AttachmentRules(EAttachmentRule::SnapToTarget, false);
    Weapon->AttachToComponent(SceneComponent, AttachmentRules, SocketName);
}

void UKTAWeaponComponent::EquipWeapon(int32 WeaponIndex)
{
    if (WeaponIndex < 0 || WeaponIndex > Weapons.Num())
        return;
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    if (CurrentWeapon)
    {
        CurrentWeapon->StopFire();
        AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponArmorySocketName);
    }

    CurrentWeapon = Weapons[WeaponIndex];
    // CurrentReloadAnimMontage = WeaponData[WeaponIndex].ReloadAnimMontage;
    const auto CurrentWeaponData =
        WeaponData.FindByPredicate([&](const FWeaponData &Data) //
                                   {
                                       return Data.WeaponClass == CurrentWeapon->GetClass(); //
                                   });
    CurrentReloadAnimMontage = CurrentWeaponData ? CurrentWeaponData->ReloadAnimMontage : nullptr;

    AttachWeaponToSocket(CurrentWeapon, Character->GetMesh(), WeaponEquipSocketName);
    EquipAnimInProgress = true;
    PlayAnimMontage(EquipAnimMontage);
}

void UKTAWeaponComponent::NextWeapon()
{
    if (!CanEquip())
        return;
    CurrentWeaponIndex = (CurrentWeaponIndex + 1) % Weapons.Num();
    EquipWeapon(CurrentWeaponIndex);
}

void UKTAWeaponComponent::PlayAnimMontage(UAnimMontage *Animation)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character)
        return;

    Character->PlayAnimMontage(Animation);
}

void UKTAWeaponComponent::InitAnimations()
{
    auto EquipFinishedNotify = FindNotifyByClass<UKTAEquipFinishedAnimNotify>(EquipAnimMontage);
    if (EquipFinishedNotify)
    {
        EquipFinishedNotify->OnNotified.AddUObject(this, &UKTAWeaponComponent::OnEquipFinished);
    }

    for (auto OneWeaponData: WeaponData)
    {
        auto ReloadFinishedNotify = FindNotifyByClass<UKTAReloadFinishedAnimNotify>(OneWeaponData.ReloadAnimMontage);
        if (!ReloadFinishedNotify)
            continue;
        
        ReloadFinishedNotify->OnNotified.AddUObject(this, &UKTAWeaponComponent::OnReloadFinished);
    }
}

void UKTAWeaponComponent::OnEquipFinished(USkeletalMeshComponent *MeshComponent)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
        return;

    EquipAnimInProgress = false;
    // UE_LOG(LogWeaponComponent, Display, TEXT("Equip finished"));
}

void UKTAWeaponComponent::OnReloadFinished(USkeletalMeshComponent *MeshComponent)
{
    ACharacter *Character = Cast<ACharacter>(GetOwner());
    if (!Character || Character->GetMesh() != MeshComponent)
        return;

    ReloadAnimInProgress = false;
    
}

bool UKTAWeaponComponent::CanFire()
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UKTAWeaponComponent::CanEquip()
{
    return !EquipAnimInProgress && !ReloadAnimInProgress;
}

bool UKTAWeaponComponent::CanReload()
{
    return CurrentWeapon && !EquipAnimInProgress && !ReloadAnimInProgress;
}

void UKTAWeaponComponent::Reload()
{
    if (!CanReload())
        return;
    ReloadAnimInProgress = true;
    PlayAnimMontage(CurrentReloadAnimMontage);
}