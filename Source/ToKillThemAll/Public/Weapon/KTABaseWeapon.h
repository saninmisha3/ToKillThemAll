// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KTABaseWeapon.generated.h"

class USkeletalMeshComponent;

UCLASS()
class TOKILLTHEMALL_API AKTABaseWeapon : public AActor
{
    GENERATED_BODY()

  public:
    // Sets default values for this actor's properties
    AKTABaseWeapon();

    virtual void StartFire();
    virtual void StopFire();

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    USkeletalMeshComponent *WeaponMesh;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    FName MuzzleSocketName = "MuzzleSocket";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TraceMaxDistance = 1500.0f;
    // Called when the game starts or when spawned
    virtual void BeginPlay() override;


    

    virtual void MakeShot();
    APlayerController *AKTABaseWeapon::GetPlayerController() const;
    bool GetPlayerViewPoint(FVector &ViewLocation, FRotator &ViewRotation) const;

    void MakeHit(FHitResult &HitResult, const FVector TraceStart, const FVector TraceEnd);
    
};
