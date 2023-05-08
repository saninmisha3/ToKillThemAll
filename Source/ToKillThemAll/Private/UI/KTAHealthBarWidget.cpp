// Kill Them All Game, All Rights Reserved

#include "UI/KTAHealthBarWidget.h"
#include "Components/ProgressBar.h"

void UKTAHealthBarWidget::SetHealthPercent(float Percent)
{
    if (!HealthProgressBar)
        return;

    const auto HealthBarVisibilitu = (Percent > PercentVisibilityThreshold || FMath::IsNearlyZero(Percent)) //
                                         ? ESlateVisibility::Hidden
                                         : ESlateVisibility::Visible;

    HealthProgressBar->SetVisibility(HealthBarVisibilitu);

    const auto HealthBarColor = Percent > PercentColorThreshold ? GoodColor : BadColor;
    HealthProgressBar->SetFillColorAndOpacity(HealthBarColor);

    HealthProgressBar->SetPercent(Percent);
}
