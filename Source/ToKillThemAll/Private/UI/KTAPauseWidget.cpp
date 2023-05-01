// Kill Them All Game, All Rights Reserved

#include "UI/KTAPauseWidget.h"
#include "Components/Button.h"
#include "Gameframework/GameModeBase.h"

void UKTAPauseWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    if (ClearPauseButton)
    {
        ClearPauseButton->OnClicked.AddDynamic(this, &UKTAPauseWidget::OnClearPause);
    }

}

void UKTAPauseWidget::OnClearPause()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->ClearPause();
}