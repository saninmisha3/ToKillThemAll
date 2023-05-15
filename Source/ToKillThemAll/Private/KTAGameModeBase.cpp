// Kill Them All Game, All Rights Reserved

#include "KTAGameModeBase.h"
#include "AI/KTAAIController.h"
#include "Components/KTARespawnComponent.h"
#include "EngineUtils.h"
#include "KTABaseCharacter.h"
#include "KTAPlayerController.h"
#include "KTAUtils.h"
#include "Player/KTAPlayerState.h"
#include "UI/KTAGameHUD.h"

DEFINE_LOG_CATEGORY_STATIC(LogKTAGameModeBase, All, All);

constexpr static int32 MinRoundTimeForRespawn = 10;

AKTAGameModeBase::AKTAGameModeBase()
{
    DefaultPawnClass = AKTABaseCharacter::StaticClass();
    PlayerControllerClass = AKTAPlayerController::StaticClass();
    HUDClass = AKTAGameHUD::StaticClass();
    PlayerStateClass = AKTAPlayerState::StaticClass();
}

void AKTAGameModeBase::StartPlay()
{
    Super::StartPlay();

    SpawnBots();
    CreateTeamsInfo();
    CurrentRound = 1;
    StartRound();

    SetMatchState(EKTAMatchState::InProgress);
}

UClass *AKTAGameModeBase::GetDefaultPawnClassForController_Implementation(AController *InController)
{
    if (InController && InController->IsA<AAIController>())
    {
        return AIPawnClass;
    }
    return Super::GetDefaultPawnClassForController_Implementation(InController);
}

void AKTAGameModeBase::Killed(AController *KillerController, AController *VictimController)
{
    const auto KillerPlayerState = KillerController ? Cast<AKTAPlayerState>(KillerController->PlayerState) : nullptr;
    const auto VictimPlayerState = VictimController ? Cast<AKTAPlayerState>(VictimController->PlayerState) : nullptr;
    if (KillerPlayerState)
    {
        KillerPlayerState->AddKill();
    }
    if (VictimPlayerState)
    {
        VictimPlayerState->AddDeath();
    }

    StartRespawn(VictimController);
}

void AKTAGameModeBase::SpawnBots()
{
    if (!GetWorld())
        return;

    for (int32 i = 0; i < GameData.PlayersNum - 1; ++i)
    {
        FActorSpawnParameters SpawnInfo;
        SpawnInfo.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        const auto KTAAIController = GetWorld()->SpawnActor<AAIController>(AAIControllerClass, SpawnInfo);
        RestartPlayer(KTAAIController);
    }
}

void AKTAGameModeBase::StartRound()
{
    RoundCountDown = GameData.RoundTime;
    GetWorldTimerManager().SetTimer(GameRoundTimerHandle, this, &AKTAGameModeBase::GetTimerUpdate, 1.0f, true);
}

void AKTAGameModeBase::GetTimerUpdate()
{
   // UE_LOG(LogKTAGameModeBase, Display, TEXT("Time: %i / Round %i/%i"), RoundCountDown, CurrentRound,
     //      GameData.RoundsNum);

    if (--RoundCountDown == 0)
    {
        GetWorldTimerManager().ClearTimer(GameRoundTimerHandle);

        if (CurrentRound + 1 < GameData.RoundsNum)
        {
            ++CurrentRound;
            ResetPlayers();
            StartRound();
        }
        else
        {
            GameOver();
        }
    }
}

void AKTAGameModeBase::ResetPlayers()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        ResetOnePlayer(It->Get());
    }
}

void AKTAGameModeBase::ResetOnePlayer(AController *Controller)
{
    if (Controller && Controller->GetPawn())
    {
        Controller->GetPawn()->Reset();
    }
    RestartPlayer(Controller);
    SetPlayerColor(Controller);
}

void AKTAGameModeBase::CreateTeamsInfo()
{
    if (!GetWorld())
        return;

    int32 TeamID = 1;
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AKTAPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->SetTeamID(TeamID);
        PlayerState->SetTeamColor(DetermineColorByID(TeamID));
        PlayerState->SetPlayerName(Controller->IsPlayerController() ? "Player" : "Bot");
        SetPlayerColor(Controller);
        TeamID = TeamID == 1 ? 2 : 1;
    }
}

FLinearColor AKTAGameModeBase::DetermineColorByID(int32 TeamID) const
{
    if (TeamID - 1 < GameData.TeamColors.Num())
    {
        return GameData.TeamColors[TeamID - 1];
    }
    else
    {
        UE_LOG(LogKTAGameModeBase, Display, TEXT("No color for TeamId"));
        return GameData.DefaultTeamColor;
    }
}

void AKTAGameModeBase::SetPlayerColor(AController *Controller)
{
    if (!Controller)
        return;

    const auto Character = Cast<AKTABaseCharacter>(Controller->GetPawn());
    if (!Character)
        return;

    const auto PlayerState = Cast<AKTAPlayerState>(Controller->PlayerState);
    if (!PlayerState)
        return;

    Character->SetPlayerColor(PlayerState->GetTeamColor());
}

void AKTAGameModeBase::LogPlayerInfo()
{
    if (!GetWorld())
        return;

    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PlayerState = Cast<AKTAPlayerState>(Controller->PlayerState);
        if (!PlayerState)
            continue;

        PlayerState->LogInfo();
    }
}

void AKTAGameModeBase::RespawnRequest(AController *Controller)
{
    ResetOnePlayer(Controller);
}

void AKTAGameModeBase::StartRespawn(AController *Controller)
{
    const bool RespawnAvailable = RoundCountDown > MinRoundTimeForRespawn + GameData.RespawnTime;
    if (!RespawnAvailable)
        return;
    const auto RespawnComponent = KTAUtils::GetKTAPlayerComponent<UKTARespawnComponent>(Controller);
    if (!RespawnComponent)
        return;

    RespawnComponent->Respawn(GameData.RespawnTime);
}

void AKTAGameModeBase::GameOver()
{
    UE_LOG(LogKTAGameModeBase, Display, TEXT("------------ Game Over ------------"));
    LogPlayerInfo();

    for (auto Pawn : TActorRange<APawn>(GetWorld()))
    {
        if (Pawn)
        {
            Pawn->TurnOff();
            Pawn->DisableInput(nullptr);
        }
    }
    SetMatchState(EKTAMatchState::GameOver);
}

void AKTAGameModeBase::SetMatchState(EKTAMatchState State)
{
    if (MatchState == State)
        return;

    MatchState = State;
    OnMatchSatateChanged.Broadcast(MatchState);
}

bool AKTAGameModeBase::SetPause(APlayerController *PC, FCanUnpause CanUnpauseDelegate)
{
    const bool PauseSet = Super::SetPause(PC, CanUnpauseDelegate);
    if (PauseSet)
    {
        SetMatchState(EKTAMatchState::Pause);
    }

    return PauseSet;
}

bool AKTAGameModeBase::ClearPause()
{
    const auto PauseCleared = Super::ClearPause();
    if (PauseCleared)
    {
        SetMatchState(EKTAMatchState::InProgress);
    }
    return PauseCleared;
}