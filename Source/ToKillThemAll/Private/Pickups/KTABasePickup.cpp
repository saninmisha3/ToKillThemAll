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
    check(CollisionComponent);
    GenerateRotationYaw();
}

// Called every frame
void AKTABasePickup::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    AddActorLocalRotation(FRotator(0.0f, RotationYaw, 0.0f));

}

void AKTABasePickup::NotifyActorBeginOverlap(AActor *OtherActor)
{
    Super::NotifyActorBeginOverlap(OtherActor);

    const auto Pawn = Cast<APawn>(OtherActor);
    if (GivePickupTool(Pawn))
        PickupWasTaken();

    //UE_LOG(LogPickupComponent, Display, TEXT("Pickup was taken"));
    //PickupWasTaken();
}

void AKTABasePickup::PickupWasTaken()
{
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (GetRootComponent())
        GetRootComponent()->SetVisibility(false, true);

    
    GetWorldTimerManager().SetTimer(RespawnTimerHandle, this, &AKTABasePickup::Respawn, RespawnTime);
}

void AKTABasePickup::Respawn()
{
    GenerateRotationYaw();
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
    if (GetRootComponent())
        GetRootComponent()->SetVisibility(true, true);
}

bool AKTABasePickup::GivePickupTool(APawn *PlayerPawn)
{
    return false;
}

void AKTABasePickup::GenerateRotationYaw()
{
    const auto Direction = FMath::RandBool() ? 1.0f : -1.0f;
    RotationYaw = FMath::RandRange(1.0f, 2.0f) * Direction;
}

bool AKTABasePickup::CouldBeTaking() const
{
    return !GetWorldTimerManager().IsTimerActive(RespawnTimerHandle);
 
}