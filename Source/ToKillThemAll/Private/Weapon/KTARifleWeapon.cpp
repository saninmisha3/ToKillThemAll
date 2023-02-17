// Kill Them All Game, All Rights Reserved


#include "Weapon/KTARifleWeapon.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Weapon/Components/KTAWeaponFXComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"

AKTARifleWeapon::AKTARifleWeapon()
{
    WeaponFXComponent = CreateDefaultSubobject<UKTAWeaponFXComponent>("WeaponFXComponent");
}

void AKTARifleWeapon::BeginPlay()
{
    Super::BeginPlay();

    check(WeaponFXComponent);
}

void AKTARifleWeapon::StartFire()
{
    // UE_LOG(LogBaseWeapon, Display, TEXT("Fire!!!"));
    InitMuzzleFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AKTARifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AKTARifleWeapon::StopFire()
{
    // UE_LOG(LogBaseWeapon, Display, TEXT("Fire!!!"));

    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetMuzzleFXVisibility(false);
}

void AKTARifleWeapon::MakeShot()
{
    if (!GetWorld() || IsAmmoEmpty())
    {
        StopFire();
        return;
    }
        

    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return;

    const FTransform SocketTransform = WeaponMesh->GetSocketTransform(MuzzleSocketName);
    const FVector TraceStart = ViewLocation;
    const auto HalfRad = FMath::DegreesToRadians(BulletSpread);
    const FVector ShootDirection = FMath::VRandCone(ViewRotation.Vector(), HalfRad);
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    FVector TraceFXEnd = TraceEnd;
    if (HitResult.bBlockingHit)
    {
        TraceFXEnd = HitResult.ImpactPoint;
        MakeDamage(HitResult);
                      WeaponFXComponent->PlayImpactFX(HitResult);
        //

        //UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }

    SpawnTraceFX(SocketTransform.GetLocation(), TraceFXEnd);
    DecreaseAmmo();
}

void AKTARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;
    DamagedActor->TakeDamage(DamageAmount, FDamageEvent{}, GetPlayerController(), this);
}
void AKTARifleWeapon::InitMuzzleFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }
    SetMuzzleFXVisibility(true);
}

void AKTARifleWeapon::SetMuzzleFXVisibility(bool Visible)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!Visible);
        MuzzleFXComponent->SetVisibility(Visible, true);
    }

}

void AKTARifleWeapon::SpawnTraceFX(const FVector &TraceStart, const FVector &TraceEnd)
{
    const auto TraceFXComponent = UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), TraceFX, TraceStart);
    if (TraceFXComponent)
    {
        TraceFXComponent->SetNiagaraVariableVec3(TraceTargetName, TraceEnd);
    }
}