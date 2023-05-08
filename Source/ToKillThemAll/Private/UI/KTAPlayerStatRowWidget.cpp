// Kill Them All Game, All Rights Reserved

#include "UI/KTAPlayerStatRowWidget.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UKTAPlayerStatRowWidget::SetPlayerName(const FText &Text)
{
    if (!PlayerNameTextBlock)
        return;
    PlayerNameTextBlock->SetText(Text);
}

void UKTAPlayerStatRowWidget::SetKills(const FText &Text)
{
    if (!KillsTextBlock)
        return;
    KillsTextBlock->SetText(Text);
}

void UKTAPlayerStatRowWidget::SetDeath(const FText &Text)
{
    if (!DeathTextBlock)
        return;
    DeathTextBlock->SetText(Text);
}

void UKTAPlayerStatRowWidget::SetTeam(const FText &Text)
{
    if (!TeamTextBlock)
        return;
    TeamTextBlock->SetText(Text);
}

void UKTAPlayerStatRowWidget::SetPlayerIndicatorVisibility(bool Visible)
{
    if (!PlayerIndicatorImage)
        return;
    PlayerIndicatorImage->SetVisibility(Visible ? ESlateVisibility::Visible : ESlateVisibility::Hidden);

}

void UKTAPlayerStatRowWidget::SetTeamColor(const FLinearColor &Color)
{
    if (!TeamImage)
        return;

    TeamImage->SetColorAndOpacity(Color);
}
