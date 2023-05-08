// Kill Them All Game, All Rights Reserved


#include "Menu/UI/KTAMenuHUD.h"
#include "UI/KTABaseWidget.h"

void AKTAMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UKTABaseWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
            MenuWidget->Show();
        }
    }

}