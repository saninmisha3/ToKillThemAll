// Kill Them All Game, All Rights Reserved


#include "UI/KTAGoToMenuWidget.h"
#include "KTAGameInstance.h"
#include "Components/Button.h"

DEFINE_LOG_CATEGORY_STATIC(LogKTAGoToMenuWidget, All, All);

void UKTAGoToMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (GoToMenuButton)
    {
        GoToMenuButton->OnClicked.AddDynamic(this, &UKTAGoToMenuWidget::OnMenuLevel);
    }
}

void UKTAGoToMenuWidget::OnMenuLevel()
{
    if (!GetWorld())
        return;

    const auto KTAGameInstance = GetWorld()->GetGameInstance<UKTAGameInstance>();
    if (!KTAGameInstance)
        return;

    if (KTAGameInstance->GetMenuLevelName().IsNone())
    {
        UE_LOG(LogKTAGoToMenuWidget, Error, TEXT("Menu level name is NONE"))
        return;
    }

    UGameplayStatics::OpenLevel(this, KTAGameInstance->GetMenuLevelName());
}