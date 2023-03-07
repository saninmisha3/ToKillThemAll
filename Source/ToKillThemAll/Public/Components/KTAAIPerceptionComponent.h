// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Perception/AIPerceptionComponent.h"
#include "KTAAIPerceptionComponent.generated.h"

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAAIPerceptionComponent : public UAIPerceptionComponent
{
	GENERATED_BODY()

		public:
    AActor *GetClosesEnemy() const;
	
};
