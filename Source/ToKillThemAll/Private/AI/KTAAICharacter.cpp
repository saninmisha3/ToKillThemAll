// Kill Them All Game, All Rights Reserved


#include "AI/KTAAICharacter.h"
#include "AI/KTAAIController.h"
#include "GameFramework/CharacterMovementComponent.h"

AKTAAICharacter::AKTAAICharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
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

