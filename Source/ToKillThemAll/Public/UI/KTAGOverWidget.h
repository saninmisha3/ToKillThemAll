// Kill Them All Game, All Rights Reserved

#pragma once

#include "KTACoreTypes.h"
#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KTAGOverWidget.generated.h"

class UVerticalBox;

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAGOverWidget : public UUserWidget
{
	GENERATED_BODY()
    public:
     virtual bool Initialize() override;

      UPROPERTY(meta = (BindWidget))
      UVerticalBox *PlayerStatBox;

      UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
      TSubclassOf<UUserWidget> PlayerStatRowWidgetClass;


  private:
    void OnMatchStateChanged(EKTAMatchState State);
    void UpdatePlayersState();
};
