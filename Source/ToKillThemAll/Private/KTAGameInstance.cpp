// Kill Them All Game, All Rights Reserved


#include "KTAGameInstance.h"
#include "Sound/KTASoundFunctionLib.h"

void UKTAGameInstance::ToggleVolume()
{
    UKTASoundFunctionLib::ToggleSoundClassVolume(MasterSoundClass);
}
