// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KTASpectatorWidget.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTASpectatorWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetRespawnTime(int32 &CountDownTime) const;
};
