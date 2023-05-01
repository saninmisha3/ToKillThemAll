// Kill Them All Game, All Rights Reserved


#include "Menu/KTAMenuPlayerController.h"

void AKTAMenuPlayerController::BeginPlay()
{
    Super::BeginPlay();
    SetInputMode(FInputModeUIOnly());
    bShowMouseCursor = true;

}