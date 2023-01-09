// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KTABaseWeapon.h"
#include "KTARifleWeapon.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API AKTARifleWeapon : public AKTABaseWeapon
{
	GENERATED_BODY()
	
public:
    virtual void StartFire() override;
    virtual void StopFire() override;

protected: 
	virtual void MakeShot() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float TimeBetweenShots = 0.1f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float BulletSpread = 1.5f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite)
    float DamageAmount = 10.0f;

  private:
    FTimerHandle ShotTimerHandle;

    void MakeDamage(const FHitResult &HitResult);
};
