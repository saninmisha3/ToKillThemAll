// Kill Them All Game, All Rights Reserved

#include "Weapon/Components/KTAWeaponFXComponent.h"
#include "Components/DecalComponent.h"
#include "Kismet/GameplayStatics.h"
#include "NiagaraFunctionLibrary.h"
#include "PhysicalMaterials/PhysicalMaterial.h"

// Sets default values for this component's properties
UKTAWeaponFXComponent::UKTAWeaponFXComponent()
{
    // Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these
    // features off to improve performance if you don't need them.
    PrimaryComponentTick.bCanEverTick = true;

    // ...
}

void UKTAWeaponFXComponent::PlayImpactFX(const FHitResult &Hit)
{
    auto ImpactData = DefaultImpactData;

    if (Hit.PhysMaterial.IsValid())
    {
        const auto PhysMat = Hit.PhysMaterial.Get();
        if (ImpactDataMap.Contains(PhysMat))
        {
            ImpactData = ImpactDataMap[PhysMat];
        }
    }
    // niagara
    UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(),               //
                                                   ImpactData.NiagaraEffect, //
                                                   Hit.ImpactPoint,          //
                                                   Hit.ImpactNormal.Rotation());

    // decal
    auto DecalComponent = UGameplayStatics::SpawnDecalAtLocation(GetWorld(),                    //
                                           ImpactData.DecalData.Material, //
                                           ImpactData.DecalData.Size,     //
                                           Hit.ImpactPoint,               //
                                           Hit.ImpactNormal.Rotation());
    if (DecalComponent)
    {
        DecalComponent->SetFadeOut(ImpactData.DecalData.LifeTime, ImpactData.DecalData.FadeOutTime);
    
    }
}
