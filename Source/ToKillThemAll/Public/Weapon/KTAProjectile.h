// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KTAProjectile.generated.h"

class USphereComponent;
class UProjectileMovementComponent;

UCLASS()
class TOKILLTHEMALL_API AKTAProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKTAProjectile();

	void SetShotDirection(const FVector &Direction)
    {
        ShotDirection = Direction;
	}

protected:
    UPROPERTY(VisibleDefaultsOnly, Category = "Weapon")
    USphereComponent *CollisionComponent;

	UPROPERTY(VisibleAnywhere, Category = "Weapon")
    UProjectileMovementComponent *MovementComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageRadius = 200.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float DamageAmount = 50.0f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    bool DoFullDamage = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Weapon")
    float LifeSeconds = 5.0f;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
    FVector ShotDirection;

	UFUNCTION()
        void OnProjectileHit (UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	AController *GetController() const;

};
