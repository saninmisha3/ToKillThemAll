// Kill Them All Game, All Rights Reserved


#include "AI/KTAAICharacter.h"
#include "AI/KTAAIController.h"

AKTAAICharacter::AKTAAICharacter(const FObjectInitializer &ObjInit) : Super(ObjInit)
{
    AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
    AIControllerClass = AKTAAIController::StaticClass();

}

