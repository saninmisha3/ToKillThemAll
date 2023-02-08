// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KTABasePickup.h"
#include "KTAAmoPickup.generated.h"
class AKTABaseWeapon;
    /**
 *
 */
UCLASS()
class TOKILLTHEMALL_API AKTAAmoPickup : public AKTABasePickup
{
    GENERATED_BODY()

  protected:
        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
        int32 ClipsAmount = 10;

        UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "10.0"))
        TSubclassOf<AKTABaseWeapon> WeaponType;

  private:
    virtual bool GivePickupTool(APawn *PlayerPawn) override;
};
