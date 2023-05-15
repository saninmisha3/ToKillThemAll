// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "KTASoundFunctionLib.generated.h"

class USoundClass;
/**
 *
 */
UCLASS()
class TOKILLTHEMALL_API UKTASoundFunctionLib : public UBlueprintFunctionLibrary
{
    GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable)
    static void SetSoundClassVolume(USoundClass *SoundClass, float Volume);

    UFUNCTION(BlueprintCallable)
    static void ToggleSoundClassVolume(USoundClass *SoundClass);

};
