// Kill Them All Game, All Rights Reserved

#include "Menu/UI/KTAMenuWidget.h"
#include "Components/Button.h"
#include "KTAGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Components/HorizontalBox.h"
#include "Menu/UI/KTALevelItemWidget.h"
#include "Sound/SoundCue.h"

DEFINE_LOG_CATEGORY_STATIC(LogKTAMenuWidget, All, All);

void UKTAMenuWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (StartGameButton)
    {
        StartGameButton->OnClicked.AddDynamic(this, &UKTAMenuWidget::OnStartGame);
    }

    if (QuitGameButton)
    {
        QuitGameButton->OnClicked.AddDynamic(this, &UKTAMenuWidget::OnQuitGame);
    }
    InitLevelItems();
}



void UKTAMenuWidget::InitLevelItems()
{
    const auto KTAGameInstance = GetKTAGameInstance();
    if (!KTAGameInstance)
        return;

    checkf(KTAGameInstance->GetLevelsData().Num() != 0, TEXT("Levels data must not be empty!"));

    if (!LevelItemsBox)
        return;
    LevelItemsBox->ClearChildren();

    for (auto LevelData : KTAGameInstance->GetLevelsData())
    {
        const auto LevelItemWidget = CreateWidget<UKTALevelItemWidget>(GetWorld(), LevelItemWidgetClass);
        if (!LevelItemWidget)
            continue;

        LevelItemWidget->SetLevelData(LevelData);
        LevelItemWidget->OnLevelSelected.AddUObject(this, &UKTAMenuWidget::OnLevelSelected);


        LevelItemsBox->AddChild(LevelItemWidget);
        LevelItemWidgets.Add(LevelItemWidget);
    }

    if (KTAGameInstance->GetStartupLevel().LevelName.IsNone())
    {
        OnLevelSelected(KTAGameInstance->GetLevelsData()[0]);
    }
    else
    {
        OnLevelSelected(KTAGameInstance->GetStartupLevel());
    }
}
void UKTAMenuWidget::OnLevelSelected(const FLevelData &Data)
{
    const auto KTAGameInstance = GetKTAGameInstance();
    if (!KTAGameInstance)
        return;

    KTAGameInstance->SetStartupLevel(Data);

    for (auto LevelItemWidget : LevelItemWidgets)
    {
        if (LevelItemWidget)
        {
            const auto IsSelected = Data.LevelName == LevelItemWidget->GetLevelData().LevelName;
            LevelItemWidget->SetSelected(IsSelected);
        }
    }
}

void UKTAMenuWidget::OnAnimationFinished_Implementation(const UWidgetAnimation *Animation)
{
    if (Animation != HideAnimation)
        return;
    const auto KTAGameInstance = GetKTAGameInstance();
    if (!KTAGameInstance)
        return;

    UGameplayStatics::OpenLevel(this, KTAGameInstance->GetStartupLevel().LevelName);
}

void UKTAMenuWidget::OnStartGame()
{
    PlayAnimation(HideAnimation);
    UGameplayStatics::PlaySound2D(GetWorld(), StartgameSound);
}

void UKTAMenuWidget::OnQuitGame()
{
    UKismetSystemLibrary::QuitGame(this, GetOwningPlayer(), EQuitPreference::Quit, true);
}



UKTAGameInstance *UKTAMenuWidget::GetKTAGameInstance() const
{
    if (!GetWorld())
        return nullptr;

    return GetWorld()->GetGameInstance<UKTAGameInstance>();
}
