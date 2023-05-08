// Kill Them All Game, All Rights Reserved

#include "Menu/UI/KTALevelItemWidget.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UKTALevelItemWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();

    if (LevelSelectButton)
    {
        LevelSelectButton->OnClicked.AddDynamic(this, &UKTALevelItemWidget::OnLevelitemClicked);
        LevelSelectButton->OnHovered.AddDynamic(this, &UKTALevelItemWidget::OnLevelItemHovered);
        LevelSelectButton->OnUnhovered.AddDynamic(this, &UKTALevelItemWidget::OnLevelItemUpHovered);
    }
}

void UKTALevelItemWidget::OnLevelitemClicked()
{
    OnLevelSelected.Broadcast(LevelData);
}

void UKTALevelItemWidget::OnLevelItemHovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Visible);
    }
}

void UKTALevelItemWidget::OnLevelItemUpHovered()
{
    if (FrameImage)
    {
        FrameImage->SetVisibility(ESlateVisibility::Hidden);
    }
}

void UKTALevelItemWidget::SetLevelData(const FLevelData &Data)
{
    LevelData = Data;

    if (LevelNameTextBlock)
    {
        LevelNameTextBlock->SetText(FText::FromName(Data.LevelDisplayName));
    }
    if (LevelImage)
    {
        LevelImage->SetBrushFromTexture(Data.levelThumb);
    }
}

void UKTALevelItemWidget::SetSelected(bool IsSelected)
{
    if (LevelImage)
    {
        LevelImage->SetColorAndOpacity(IsSelected ? FLinearColor::Red : FLinearColor::White);

    }
}