// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KTAPauseWidget.generated.h"

class UButton;
    /**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAPauseWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
    virtual bool Initialize() override;

protected:
    UPROPERTY(meta = (BindWidget))
    UButton *ClearPauseButton;

    private:
    UFUNCTION()
    void OnClearPause();

};
