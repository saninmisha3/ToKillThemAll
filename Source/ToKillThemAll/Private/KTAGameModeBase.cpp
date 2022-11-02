// Kill Them All Game, All Rights Reserved

#include "KTAGameModeBase.h"
#include "KTABaseCharacter.h"
#include "KTAPlayerController.h"

AKTAGameModeBase::AKTAGameModeBase()
{
    DefaultPawnClass = AKTABaseCharacter::StaticClass();
    PlayerControllerClass = AKTAPlayerController::StaticClass();
}
