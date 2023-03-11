// Kill Them All Game, All Rights Reserved


#include "AI/KTAAICharacter.h"
#include "AI/KTAAIController.h"
#include "Components/KTAAIWeaponComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

AKTAAICharacter::AKTAAICharacter(const FObjectInitializer &ObjInit):
    Super(ObjInit.SetDefaultSubobjectClass<UKTAAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKTAAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

}

void AKTAAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto KTAController = Cast<AKTAAIController>(Controller);
    if (KTAController && KTAController->BrainComponent)
    {
        KTAController->BrainComponent->Cleanup();
    }

}

