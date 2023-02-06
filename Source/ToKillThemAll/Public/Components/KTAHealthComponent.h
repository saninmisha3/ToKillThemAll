// Kill Them All Game, All Rights Reserved

#pragma once

#include "Components/ActorComponent.h"
#include "CoreMinimal.h"
#include "KTACoreTypes.h"
#include "KTAHealthComponent.generated.h"



UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TOKILLTHEMALL_API UKTAHealthComponent : public UActorComponent
{
    GENERATED_BODY()

  public:
    // Sets default values for this component's properties
    UKTAHealthComponent();

    FOnDeathSignature OnDeath;
    FOnHealthChangedSignature OnHealthChanged;
    FTimerHandle HealHandle;

    float GetHealth() const
    {
        return Health;
    }

    UFUNCTION(BlueprintCallable, Category = "Health")
    bool IsDead() const
    {
        return FMath::IsNearlyZero(Health);
    }

    UFUNCTION(BlueprintCallable, Category = "Health")
    float GetHealthPercent() const
    {
        return Health / MaxHealth;
    }


    //UFUNCTION(BlueprintCallable)
    //bool HealthIsFull() const {return Health <= 0.0f;}



  protected:
    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Helth", meta = (ClampMin = "0.0", ClampMax = "1000.0"))
    float MaxHealth = 100.0f;
    // Called when the game starts
    virtual void BeginPlay() override;

    
    
    UPROPERTY(EditAnywhere, Category = "Heal")
    bool AutoHeal = false;

    UPROPERTY(EditAnywhere, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealUpdateTime = 0.3f;

    UPROPERTY(EditAnywhere, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealDelay = 3.0f;

    UPROPERTY(EditAnywhere, Category = "Heal", meta = (EditCondition = "AutoHeal"))
    float HealModifier = 1.0f;

  private:

    FTimerHandle HealTimerHandle;
    float Health = 0.0f;

    
     UFUNCTION()
     void OnTakeAnyDamage(AActor *DamagedActor, float Damage, const class UDamageType *DamageType,
                               class AController *InstigatedBy, AActor *DamageCauser);
     
     void HealUpdate();
     void SetHealth(float NewHealth);
};
