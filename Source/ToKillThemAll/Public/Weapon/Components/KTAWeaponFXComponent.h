// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "Components/ActorComponent.h"
#include "KTAWeaponFXComponent.generated.h"

class UNiagaraSystem;
class UPhysicalMaterial;

UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKILLTHEMALL_API UKTAWeaponFXComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKTAWeaponFXComponent();

	void PlayImpactFX(const FHitResult &Hit);

	protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")
    FImpactData DefaultImpactData;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "VFX")

    TMap<UPhysicalMaterial *, FImpactData> ImpactDataMap;
};
