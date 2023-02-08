// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KTABasePickup.generated.h"

class USphereComponent;

UCLASS()
class TOKILLTHEMALL_API AKTABasePickup : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AKTABasePickup();

protected:
    UPROPERTY(VisibleAnywhere, Category = "Pickup")
	USphereComponent *CollisionComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Pickup")
    float RespawnTime = 5.0f;

	virtual void BeginPlay() override;
    virtual void NotifyActorBeginOverlap(AActor *OtherActor) override;

  public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	private:
    float RotationYaw = 0.0f;
    virtual bool GivePickupTool(APawn* PlayerPawn);
    void PickupWasTaken();
    void Respawn();
    void GenerateRotationYaw();
};
