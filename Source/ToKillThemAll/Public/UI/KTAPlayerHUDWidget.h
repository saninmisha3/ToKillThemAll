// Kill Them All Game, All Rights Reserved

#pragma once

#include "UI/KTABaseWidget.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAPlayerHUDWidget.generated.h"

class UProgressBar;

UCLASS()
class TOKILLTHEMALL_API UKTAPlayerHUDWidget : public UKTABaseWidget
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

    UFUNCTION(BlueprintImplementableEvent, Category = "UI")
    void OnTakeDamage();

    UFUNCTION(BlueprintCallable, Category = "UI")
    int32 GetKillsNum() const;

    UFUNCTION(BlueprintCallable, Category = "UI")
    FString FormatBullets(int32 BulletsNum) const;

  protected:
    UPROPERTY(meta = (BindWidget))
    UProgressBar *HealthProgressBar;

    UPROPERTY(meta = (BindWidgetAnim), Transient)
    UWidgetAnimation *DamageAnimation;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    float PercentColorThreshold = 0.3f;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor GoodColor = FLinearColor::White;

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "UI")
    FLinearColor BadColor = FLinearColor::Red;

    virtual void NativeOnInitialized() override;

  private:
    void OnHealthChanged(float Health, float HealthDelta);
    void OnNewPawn(APawn *NewPawn);
    void UpdateHealthBar();
};
