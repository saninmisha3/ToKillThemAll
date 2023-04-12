// Kill Them All Game, All Rights Reserved


#include "KTAPlayerController.h"
#include "Components/KTARespawnComponent.h"



AKTAPlayerController::AKTAPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UKTARespawnComponent>("RespawnComponent");
}
