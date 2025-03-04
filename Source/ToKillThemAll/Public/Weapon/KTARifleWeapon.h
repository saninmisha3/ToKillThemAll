// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KTABaseWeapon.h"
#include "KTARifleWeapon.generated.h"

class UKTAWeaponFXComponent;
class UNiagaraComponent;
class UNiagaraSystem;
class UAudioComponent;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTARifleWeapon : public AKTABaseWeapon
{
    GENERATED_BODY()

  public:
    AKTARifleWeapon();

    virtual void StartFire() override;
    virtual void StopFire() override;

    virtual void Zoom(bool Enabled) override;

  protected:
    virtual void BeginPlay() override;
    virtual void MakeShot() override;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 10.0f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    UNiagaraSystem *TraceFX;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FString TraceTargetName = "TraceTarget";

    UPROPERTY(VisibleAnywhere, Category = "VFX")
    UKTAWeaponFXComponent *WeaponFXComponent;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float FOVZoomAngle = 50.0f;

  private:
    FTimerHandle ShotTimerHandle;

    UPROPERTY()
    UNiagaraComponent *MuzzleFXComponent;

    UPROPERTY()
    UAudioComponent *FireAudioComponent;

    void MakeDamage(const FHitResult &HitResult);
    void InitFX();
    void SetFXActive(bool IsActive);
    void SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd);

    float DefaultCameraFOV = 90.0f;
};
