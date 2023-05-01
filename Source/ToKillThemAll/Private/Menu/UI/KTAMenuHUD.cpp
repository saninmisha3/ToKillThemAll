// Kill Them All Game, All Rights Reserved


#include "Menu/UI/KTAMenuHUD.h"
#include "Blueprint/UserWidget.h"

void AKTAMenuHUD::BeginPlay()
{
    Super::BeginPlay();

    if (MenuWidgetClass)
    {
        const auto MenuWidget = CreateWidget<UUserWidget>(GetWorld(), MenuWidgetClass);
        if (MenuWidget)
        {
            MenuWidget->AddToViewport();
        }
    }

}