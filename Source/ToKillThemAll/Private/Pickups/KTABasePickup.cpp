// Kill Them All Game, All Rights Reserved


#include "Pickups/KTABasePickup.h"
#include "Components/SphereComponent.h"

DEFINE_LOG_CATEGORY_STATIC(LogPickupComponent, All, All);

// Sets default values
AKTABasePickup::AKTABasePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(50.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled ::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    SetRootComponent(CollisionComponent);
}

// Called when the game starts or when spawned
void AKTABasePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKTABasePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AKTABasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    UE_LOG(LogPickupComponent, Display, TEXT("Pickup was taken"));
    Destroy();
}