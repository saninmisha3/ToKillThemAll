// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Weapon/KTABaseWeapon.h"
#include "KTALauncherWeapon.generated.h"

class AKTAProjectile;

UCLASS()
class TOKILLTHEMALL_API AKTALauncherWeapon : public AKTABaseWeapon
{
	GENERATED_BODY()

  public:
    virtual void StartFire() override;

    protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    TSubclassOf<AKTAProjectile> ProjectileClass;

    virtual void MakeShot() override;
};
