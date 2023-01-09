// Kill Them All Game, All Rights Reserved

#include "KTAGameModeBase.h"
#include "KTABaseCharacter.h"
#include "KTAPlayerController.h"
#include "UI/KTAGameHUD.h"

AKTAGameModeBase::AKTAGameModeBase()
{
    DefaultPawnClass = AKTABaseCharacter::StaticClass();
    PlayerControllerClass = AKTAPlayerController::StaticClass();
    HUDClass = AKTAGameHUD::StaticClass();
}
