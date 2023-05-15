// Kill Them All Game, All Rights Reserved


#include "Sound/KTASoundFunctionLib.h"
#include "Sound/SoundClass.h"


DEFINE_LOG_CATEGORY_STATIC(LogKTASoundFuncLib, All, All);

void UKTASoundFunctionLib::SetSoundClassVolume(USoundClass *SoundClass, float Volume)
{
    if (!SoundClass)
        return;

    SoundClass->Properties.Volume = FMath::Clamp(Volume,0.0f, 1.0f);
    //UE_LOG(LogKTASoundFuncLib, Display, TEXT("Sound class volume was changed: %s = %f"), SoundClass->GetName(),
   //        SoundClass->Properties.Volume;
}


void UKTASoundFunctionLib::ToggleSoundClassVolume(USoundClass *SoundClass)
{
    if (!SoundClass)
        return;

    const auto NextVolume = SoundClass->Properties.Volume > 0.0f ? 0.0f : 1.0f;
    SetSoundClassVolume(SoundClass, NextVolume);
}