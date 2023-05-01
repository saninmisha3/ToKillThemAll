// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "KTAMenuPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API AKTAMenuPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	protected:
    virtual void BeginPlay() override;

};
