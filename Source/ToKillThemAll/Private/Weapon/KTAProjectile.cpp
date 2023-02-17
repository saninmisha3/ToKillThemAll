// Kill Them All Game, All Rights Reserved

#include "Weapon/KTAProjectile.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Weapon/Components/KTAWeaponFXComponent.h"

// Sets default values
AKTAProjectile::AKTAProjectile()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = false;

    CollisionComponent = CreateDefaultSubobject<USphereComponent>("SphereComponent");
    CollisionComponent->InitSphereRadius(5.0f);
    CollisionComponent->SetCollisionEnabled(ECollisionEnabled ::QueryOnly);
    CollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Block);
    CollisionComponent->bReturnMaterialOnMove = true;
    SetRootComponent(CollisionComponent);

    MovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("MovementComponent");
    WeaponFXComponent = CreateDefaultSubobject<UKTAWeaponFXComponent>("WeaponFXComponent");
}

// Called when the game starts or when spawned
void AKTAProjectile::BeginPlay()
{
    Super::BeginPlay();

    check(MovementComponent);
    check(CollisionComponent);
    check(WeaponFXComponent);

    MovementComponent->Velocity = ShotDirection * MovementComponent->InitialSpeed;


    CollisionComponent->IgnoreActorWhenMoving(GetOwner(), true);
    CollisionComponent->OnComponentHit.AddDynamic(this, &AKTAProjectile::OnProjectileHit);
    SetLifeSpan(LifeSeconds);
}

void AKTAProjectile::OnProjectileHit(UPrimitiveComponent *HitComponent, AActor *OtherActor,
                                     UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
    if (!GetWorld())
        return;

    MovementComponent->StopMovementImmediately();

    // make damage
    UGameplayStatics::ApplyRadialDamage(GetWorld(),                 //
                                        DamageAmount,               //
                                        GetActorLocation(),         //
                                        DamageRadius,               //
                                        UDamageType::StaticClass(), //
                                        {GetOwner()},               //
                                        this,                       //
                                        GetController(),            //
                                        DoFullDamage);
    
    //DrawDebugSphere(GetWorld(), GetActorLocation(), DamageRadius, 24, FColor::Red, false, 5.0f);
    WeaponFXComponent->PlayImpactFX(Hit);
        Destroy();
}

AController *AKTAProjectile::GetController() const
{
    const auto Pawn = Cast<APawn>(GetOwner());
    return Pawn ? Pawn->GetController():nullptr;
}
