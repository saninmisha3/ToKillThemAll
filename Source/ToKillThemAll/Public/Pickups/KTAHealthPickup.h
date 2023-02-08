// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Pickups/KTABasePickup.h"
#include "KTAHealthPickup.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API AKTAHealthPickup : public AKTABasePickup
{
	GENERATED_BODY()

	  protected:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup", meta = (ClampMin = "1.0", ClampMax = "100.0"))
    int32 HealthAmount = 100;


	private:
    virtual bool GivePickupTool(APawn *PlayerPawn) override;
};
