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


    void StartFire();
    void StopFire();
    void NextWeapon();
    void Reload();



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
    UAnimMontage* EquipAnimMontage;

  private:
    UPROPERTY()
    AKTABaseWeapon *CurrentWeapon = nullptr;

    UPROPERTY()
    TArray<AKTABaseWeapon*> Weapons;

    UPROPERTY()
    UAnimMontage *CurrentReloadAnimMontage = nullptr;

    int32 CurrentWeaponIndex = 0;
    bool EquipAnimInProgress = false;
    bool ReloadAnimInProgress = false;

    void SpawnWeapons();
    void AttachWeaponToSocket(AKTABaseWeapon *Weapon, USceneComponent *SceneComponent,
                                                   const FName &SocketName);
    void EquipWeapon(int32 WeaponIndex);

    void PlayAnimMontage(UAnimMontage *Animation);

    void InitAnimations();
    void OnEquipFinished(USkeletalMeshComponent* MeshComponent);
    void OnReloadFinished(USkeletalMeshComponent *MeshComponent);

    bool CanFire();
    bool CanEquip();
    bool CanReload();

    void OnEmptyClip();
    void ChangeClip();

    
};
