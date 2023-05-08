#include "UI/KTAGameHUD.h"
#include "Engine/Canvas.h"
#include "UI/KTABaseWidget.h"

DEFINE_LOG_CATEGORY_STATIC(LogKTAGameHUD, All, All);

void AKTAGameHUD::BeginPlay()
{
    Super::BeginPlay();

    GameWidgets.Add(EKTAMatchState::InProgress, CreateWidget<UKTABaseWidget>(GetWorld(), PlayerHUDWidgetClass));
    GameWidgets.Add(EKTAMatchState::Pause, CreateWidget<UKTABaseWidget>(GetWorld(), PauseWidgetClass));
    GameWidgets.Add(EKTAMatchState::GameOver, CreateWidget<UKTABaseWidget>(GetWorld(), GameOverWidgetClass));

    for (auto GameWidgetPair : GameWidgets)
    {
        const auto GameWidget = GameWidgetPair.Value;
        if (!GameWidget)
            continue;
       
        GameWidget->AddToViewport();
        GameWidget->SetVisibility(ESlateVisibility::Hidden);
    }


    if (GetWorld())
    {
        const auto GameMode = Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchSatateChanged.AddUObject(this, &AKTAGameHUD::OnMatchStateChanged);
        }
    }
}

void AKTAGameHUD::DrawHUD()
{
    Super::DrawHUD();
    //DrawCrossHaie();
}

void AKTAGameHUD::DrawCrossHaie()
{
    int32 SizeX = Canvas->SizeX;
    int32 SizeY = Canvas->SizeY;
    const TInterval<float> Center(SizeX * 0.5f, SizeY * 0.5f);

    const float HalfLineSize = 10.0f;
    const float LineThickness = 2.0f;
    const FLinearColor LineColor = FLinearColor::Green;

    DrawLine(Center.Min - HalfLineSize, Center.Max, Center.Min + HalfLineSize, Center.Max, LineColor, LineThickness);
    DrawLine(Center.Min, Center.Max - HalfLineSize, Center.Min, Center.Max + HalfLineSize, LineColor, LineThickness);
}

void AKTAGameHUD::OnMatchStateChanged(EKTAMatchState State)
{
    if (CurrentWinget)
    {
        CurrentWinget->SetVisibility(ESlateVisibility::Hidden);
    }

    if (GameWidgets.Contains(State))
    {
        CurrentWinget = GameWidgets[State];
    }

    if (CurrentWinget)
    {
        CurrentWinget->SetVisibility(ESlateVisibility::Visible);
        CurrentWinget->Show();
    }


    //UE_LOG(LogKTAGameHUD, Display, TEXT("Match Satate changed: %s"), *UEnum::GetValueAsString(State));
}