// Kill Them All Game, All Rights Reserved


#include "Player/KTAPlayerState.h"

DEFINE_LOG_CATEGORY_STATIC(LogKTAPlayerState, All, All);


void AKTAPlayerState::LogInfo()
{

	UE_LOG(LogKTAPlayerState, Display, TEXT("TeamID: %i, Kills: %i, Death: %i"), TeamID, KillsNum, DeathNum);

}
