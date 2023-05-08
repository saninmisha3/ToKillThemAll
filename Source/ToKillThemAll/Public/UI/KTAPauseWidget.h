// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "UI/KTABaseWidget.h"
#include "KTAPauseWidget.generated.h"

class UButton;
    /**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAPauseWidget : public UKTABaseWidget
{
	GENERATED_BODY()
	
public:
    

protected:
    UPROPERTY(meta = (BindWidget))
    UButton *ClearPauseButton;

    private:

    virtual void NativeOnInitialized() override;

    UFUNCTION()
    void OnClearPause();

};
