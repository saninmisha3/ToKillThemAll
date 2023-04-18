// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "KTARespawnComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TOKILLTHEMALL_API UKTARespawnComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UKTARespawnComponent();

  void Respawn(int32 RespawnTime);

  int32 GetRespawnCountDown() const
  {
      return RespawnCountDown;
  }
  bool IsRespawnInProgress() const;

private:
  FTimerHandle RespawnTimerHandle;
  int32 RespawnCountDown = 0;

  void RespawnTimerUpdate();

};
