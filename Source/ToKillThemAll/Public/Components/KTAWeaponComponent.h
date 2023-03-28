// Kill Them All Game, All Rights Reserved

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAWeaponComponent.generated.h"

class AKTABaseWeapon;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKILLTHEMALL_API UKTAWeaponComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UKTAWeaponComponent();

    virtual void StartFire();
    void StopFire();
    virtual void NextWeapon();
    void Reload();

    bool GetCurrentWeponUIData(FWeaponUIData &UIData) const;
    bool GetCurrentWeponAmmoData(FAmmoData &AmmoData) const;

    bool TryToAddAmmo(TSubclassOf<AKTABaseWeapon> WeaponType, int32 ClipsAmount);
    bool NeedAmmo(TSubclassOf<AKTABaseWeapon> WeaponType);

  protected:
    // Called when the game starts
    virtual void BeginPlay() override;
    virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    TArray<FWeaponData> WeaponData;

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponEquipSocketName = "WeaponSocket";

    UPROPERTY(EditDefaultsOnly, Category = "Weapon")
    FName WeaponArmorySocketName = "ArmorySocket";

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *EquipAnimMontage;

    UPROPERTY()
    AKTABaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AKTABaseWeapon *> Weapons;

    bool CanFire();
    bool CanEquip();
    void EquipWeapon(int32 WeaponIndex);

    int32 CurrentWeaponIndex = 0;

  private:
    UPROPERTY()
    UAnimMontage *CurrentReloadAnimMontage = nullptr;

    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AKTABaseWeapon *Weapon, USceneComponent *SceneComponent, const FName &SocketName);

    void PlayAnimMontage(UAnimMontage *Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent *MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent *MeshComponent);

    bool CanReload();

    void OnEmptyClip(AKTABaseWeapon *AmmoEmptyWeapon);
    void ChangeClip();
};
