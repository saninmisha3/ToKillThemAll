// Kill Them All Game, All Rights Reserved

#include "UI/KTAPauseWidget.h"
#include "Components/Button.h"
#include "Gameframework/GameModeBase.h"

bool UKTAPauseWidget::Initialize()
{
    const auto InitStatus = Super::Initialize();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UKTAPauseWidget::OnClearPause);
    }

    return InitStatus;
}

void UKTAPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}