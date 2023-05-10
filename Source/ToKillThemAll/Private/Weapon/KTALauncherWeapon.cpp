// Kill Them All Game, All Rights Reserved


#include "Weapon/KTALauncherWeapon.h"
#include "Weapon/KTAProjectile.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

DEFINE_LOG_CATEGORY_STATIC(LogLauncher, All, All);

void AKTALauncherWeapon::StartFire()
{
    MakeShot();
}

void AKTALauncherWeapon::MakeShot()
{
    if (!GetWorld())
    {
        StopFire();
        return;
    }
    
    if (IsAmmoEmpty())
    {
        StopFire();
        UGameplayStatics::SpawnSoundAtLocation(GetWorld(), NoAmmoSound, GetActorLocation());

        return;
    }

    FVector ViewLocation;
    FRotator ViewRotation;
    if (!GetPlayerViewPoint(ViewLocation, ViewRotation))
        return;

    const FVector TraceStart = ViewLocation;
    const FVector ShootDirection = ViewRotation.Vector();
    const FVector TraceEnd = TraceStart + ShootDirection * TraceMaxDistance;

    FHitResult HitResult;
    MakeHit(HitResult, TraceStart, TraceEnd);

    const FVector EndPoint = HitResult.bBlockingHit ? HitResult.ImpactPoint : TraceEnd;
    UE_LOG(LogLauncher, Display, TEXT("Hit: %s, End: %s"), *EndPoint.ToString(), *TraceEnd.ToString());
    const FVector Direction = (EndPoint - WeaponMesh->GetSocketLocation(MuzzleSocketName)).GetSafeNormal();



    const FTransform SpawnTranform(FRotator::ZeroRotator, WeaponMesh->GetSocketLocation(MuzzleSocketName));
    AKTAProjectile *Projectile = GetWorld()->SpawnActorDeferred<AKTAProjectile>(ProjectileClass, SpawnTranform);
    if (Projectile)
    {
        Projectile->SetShotDirection(Direction);
        Projectile->SetOwner(GetOwner());
        Projectile->FinishSpawning(SpawnTranform);
    
    }
    DecreaseAmmo();
    SpawnMuzzleFX();
    UGameplayStatics::SpawnSoundAttached(FireSound, WeaponMesh, MuzzleSocketName);
}