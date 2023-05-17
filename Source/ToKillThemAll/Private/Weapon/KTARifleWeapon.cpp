// Kill Them All Game, All Rights Reserved

#include "Weapon/KTARifleWeapon.h"
#include "Components/AudioComponent.h"
#include "DrawDebugHelpers.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundCue.h"
#include "Weapon/Components/KTAWeaponFXComponent.h"

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
    InitFX();
    GetWorldTimerManager().SetTimer(ShotTimerHandle, this, &AKTARifleWeapon::MakeShot, TimeBetweenShots, true);
    MakeShot();
}

void AKTARifleWeapon::StopFire()
{
    // UE_LOG(LogBaseWeapon, Display, TEXT("Fire!!!"));

    GetWorldTimerManager().ClearTimer(ShotTimerHandle);
    SetFXActive(false);
}

void AKTARifleWeapon::Zoom(bool Enabled)
{
    const auto Controller = Cast<APlayerController>(GetPlayerController());
    if (!Controller || !Controller->PlayerCameraManager)
        return;

    if (Enabled)
    {
        DefaultCameraFOV = Controller->PlayerCameraManager->GetFOVAngle();
    }

    Controller->PlayerCameraManager->SetFOV(Enabled ? FOVZoomAngle : DefaultCameraFOV);
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

        // UE_LOG(LogBaseWeapon, Display, TEXT("Bone: %s"), *HitResult.BoneName.ToString());
    }

    SpawnTraceFX(SocketTransform.GetLocation(), TraceFXEnd);
    DecreaseAmmo();
}

void AKTARifleWeapon::MakeDamage(const FHitResult &HitResult)
{
    const auto DamagedActor = HitResult.GetActor();
    if (!DamagedActor)
        return;

    FPointDamageEvent PointDamageEvent;
    PointDamageEvent.HitInfo = HitResult;
    DamagedActor->TakeDamage(DamageAmount, PointDamageEvent, GetPlayerController(), this);
}

void AKTARifleWeapon::InitFX()
{
    if (!MuzzleFXComponent)
    {
        MuzzleFXComponent = SpawnMuzzleFX();
    }

    if (!FireAudioComponent)
    {
        FireAudioComponent = UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
    }
    SetFXActive(true);
}

void AKTARifleWeapon::SetFXActive(bool IsActive)
{
    if (MuzzleFXComponent)
    {
        MuzzleFXComponent->SetPaused(!IsActive);
        MuzzleFXComponent->SetVisibility(IsActive, true);
    }

    if (FireAudioComponent)
    {
        IsActive ? FireAudioComponent->Play() : FireAudioComponent->Stop();
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