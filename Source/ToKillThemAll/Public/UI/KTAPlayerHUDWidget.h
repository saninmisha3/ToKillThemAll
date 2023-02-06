// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "KTACoreTypes.h"
#include "KTAPlayerHUDWidget.generated.h"

UCLASS()
class TOKILLTHEMALL_API UKTAPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

  public:
    UFUNCTION(BlueprintCallable, Category = "UI")
    float Get_HealthPercent() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeponUIData(FWeaponUIData &UIData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool GetCurrentWeponAmmoData(FAmmoData &AmmoData) const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerAlive() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    bool IsPlayerSpectating() const;

};
