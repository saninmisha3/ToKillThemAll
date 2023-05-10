// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KTACoreTypes.h"
#include "KTABaseWeapon.generated.h"


class USkeletalMeshComponent;
class UNiagaraSystem;
class UNiagaraComponent;
class USoundCue;

UCLASS()
class TOKILLTHEMALL_API AKTABaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    AKTABaseWeapon();

    FOnClipEmptySignature OnClipEmpty;

    virtual void StartFire();
    virtual void StopFire();

    void ChangeClip();
    bool CanReload() const;

    FWeaponUIData GetUIData() const
    {
    return UIData;
    }
    FAmmoData GetAmmoData() const
    {
        return CurrentAmmo;
    }

    bool TryToAddAmmo(int32 ClipsAmount);
    bool IsAmmoEmpty() const;
    bool IsAmmoFull() const;

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon", meta = (EditCondition = "!Infinite"))
    FAmmoData DefaultAmmo{15, 10, false};

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FWeaponUIData UIData;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *MuzzleFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue *FireSound;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void MakeShot();
    APlayerController *AKTABaseWeapon::GetPlayerController() const;
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;

    void MakeHit(FHitResult &HitResult, const FVector TraceStart, const FVector TraceEnd);

    void DecreaseAmmo();
    
    bool IsClipEmpty() const;
    

    void LogAmmo();

    UNiagaraComponent *SpawnMuzzleFX();
  private:
    FAmmoData CurrentAmmo;
};
