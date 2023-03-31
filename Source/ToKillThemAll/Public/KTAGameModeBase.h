 // Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "KTACoreTypes.h"
#include "KTAGameModeBase.generated.h"

/**
 * 
 */

class AAIController;

UCLASS()
class TOKILLTHEMALL_API AKTAGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
    AKTAGameModeBase();

	virtual void StartPlay() override;
    virtual UClass *GetDefaultPawnClassForController_Implementation(AController *InController) override;

	protected:
    UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<AAIController> AAIControllerClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
    TSubclassOf<APawn> AIPawnClass;

	UPROPERTY(EditDefaultsOnly, Category = "Game")
    FGameData GameData;

	private:
    int32 CurrentRound = 1;
    int32 RoundCountDown = 0;
    FTimerHandle GameRoundTimerHandle;

    void SpawnBots();
    void StartRound();
    void GetTimerUpdate();

    void ResetPlayers();
    void ResetOnePlayer(AController* Controller);

    void CreateTeamsInfo();
    FLinearColor DetermineColorByID(int32 TeamID) const;
    void SetPlayerColor(AController *Controller);
};
