// Kill Them All Game, All Rights Reserved


#include "UI/KTAGOverWidget.h"
#include "Components/VerticalBox.h"
#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"
#include "KTAGameModeBase.h"
#include "KTAUtils.h"
#include "Player/KTAPlayerState.h"
#include "UI/KTAPlayerStatRowWidget.h"


void UKTAGOverWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GetWorld())
    {
        const auto GameMode = Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchSatateChanged.AddUObject(this, &UKTAGOverWidget::OnMatchStateChanged);
        }
    }

    if (ResetLevelButton)
    {
        ResetLevelButton->OnClicked.AddDynamic(this, &UKTAGOverWidget::OnResetLevel);
    }
}


void UKTAGOverWidget::OnMatchStateChanged(EKTAMatchState State)
{
    
    if (State == EKTAMatchState::GameOver)
    {
        UpdatePlayersState();
    }
    
}

void UKTAGOverWidget::UpdatePlayersState()
{
    
    if (!GetWorld() || !PlayerStatBox)
        return;

    PlayerStatBox->ClearChildren();
    for (auto It = GetWorld()->GetControllerIterator(); It; ++It)
    {
        
        

        
        const auto Controller = It->Get();
        if (!Controller)
            continue;

        const auto PalyerState = Cast<AKTAPlayerState>(Controller->PlayerState);
        if (!PalyerState)
            continue;

        
        const auto PlayerStatRowWidget = CreateWidget<UKTAPlayerStatRowWidget>(GetWorld(), PlayerStatRowWidgetClass);
        PlayerStatRowWidget->SetPlayerName(FText::FromString(PalyerState->GetPlayerName()));
        PlayerStatRowWidget->SetKills(KTAUtils::TextFromInt(PalyerState->GetKillsNum()));
        PlayerStatRowWidget->SetDeath(KTAUtils::TextFromInt(PalyerState->GetDeathNum()));
        PlayerStatRowWidget->SetTeam(KTAUtils::TextFromInt(PalyerState->GetTeamID()));
        PlayerStatRowWidget->SetPlayerIndicatorVisibility(Controller->IsPlayerController());
        PlayerStatRowWidget->SetTeamColor(PalyerState->GetTeamColor());
        
        PlayerStatBox->AddChild(PlayerStatRowWidget);
        
    }
    
}

void UKTAGOverWidget::OnResetLevel()
{
    const FString CurrentLevelName = UGameplayStatics::GetCurrentLevelName(this);
    UGameplayStatics::OpenLevel(this, FName(CurrentLevelName));
}