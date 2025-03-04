// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KTABaseCharacter.generated.h"

class UKTAHealthComponent;
class UKTAWeaponComponent;
class USoundCue;

UCLASS() class TOKILLTHEMALL_API AKTABaseCharacter : public ACharacter
{
    GENERATED_BODY()

  public:
    // Sets default values for this character's properties
    AKTABaseCharacter(const FObjectInitializer &ObjInt);

  protected:
    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKTAHealthComponent *HealthComponent;

    UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    UKTAWeaponComponent *WeaponComponent;

    UPROPERTY(EditDefaultsOnly, Category = "Animation")
    UAnimMontage *DeathAnimMontage;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    float LifeSpanOnDeath = 5.0f;

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamageVelocity = FVector2D(900.0f, 1200.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Damage")
    FVector2D LandedDamage = FVector2D(10.0f, 100.0f);

    UPROPERTY(EditDefaultsOnly, Category = "Material")
    FName MaterialColorName = "Paint Color";

    UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Sound")
    USoundCue *DeathSound;

    // UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    // USpringArmComponent *SpringArmComponent;

    // UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Components")
    // USpringArmComponent *SpringArmComponent;

    // Called when the game starts or when spawned
    virtual void BeginPlay() override;

    virtual void OnDeath();

    virtual void OnHealthChanged(float Health, float HealthDelta);

  public:
    // Called every frame
    virtual void Tick(float DeltaTime) override;
    virtual void TurnOff() override;
    virtual void Reset() override;
    // Called to bind functionality to input

    UFUNCTION(BlueprintCallable, Category = "Movement")
    virtual bool IsRunning() const;

    UFUNCTION(BlueprintCallable, Category = "Movement")
    float GetMovementDirection() const;

    void SetPlayerColor(const FLinearColor &Color);

  private:
    UFUNCTION()
    void OnGroundLanded(const FHitResult &Hit);
};
