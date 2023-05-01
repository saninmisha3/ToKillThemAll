// Kill Them All Game, All Rights Reserved


#include "Menu/KTAMenuGameModeBase.h"
#include "Menu/UI/KTAMenuHUD.h"
#include "Menu/KTAMenuPlayerController.h"

AKTAMenuGameModeBase::AKTAMenuGameModeBase()
{
    PlayerControllerClass = AKTAMenuPlayerController::StaticClass();
    HUDClass = AKTAMenuHUD::StaticClass();
}