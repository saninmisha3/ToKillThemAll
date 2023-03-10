// Kill Them All Game, All Rights Reserved

#pragma once

#include "Components/KTAWeaponComponent.h"
#include "CoreMinimal.h"
#include "KTAAIWeaponComponent.generated.h"

/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTAAIWeaponComponent : public UKTAWeaponComponent
{
    GENERATED_BODY()

  public:
    virtual void StartFire() override;
    virtual void NextWeapon() override;
};
