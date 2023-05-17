// Kill Them All Game, All Rights Reserved

#include "KTABaseCharacter.h"
#include "Components/KTAWeaponComponent.h"
#include "Components/KTACharacterMovementComponent.h"
#include "Components/KTAHealthComponent.h"
#include "Components/TextRenderComponent.h"
#include "Components/CapsuleComponent.h"
#include "Engine/Engine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "KTABaseCharacter.h"

DEFINE_LOG_CATEGORY_STATIC(BaseCharacterLog, All, All);

// Sets default values
AKTABaseCharacter::AKTABaseCharacter(const FObjectInitializer &ObjInt)
    : Super(ObjInt.SetDefaultSubobjectClass<UKTACharacterMovementComponent>(ACharacter::CharacterMovementComponentName))
{
    // Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need
    // it.
    PrimaryActorTick.bCanEverTick = true;



    HealthComponent = CreateDefaultSubobject<UKTAHealthComponent>("HealthComponent");
    WeaponComponent = CreateDefaultSubobject<UKTAWeaponComponent>("WeaponComponent");
}

// Called when the game starts or when spawned
void AKTABaseCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(HealthComponent);
    check(GetCharacterMovement());
    check(GetMesh());

    OnHealthChanged(HealthComponent->GetHealth(), 0.0f);
    HealthComponent->OnDeath.AddUObject(this, &AKTABaseCharacter::OnDeath);
    HealthComponent->OnHealthChanged.AddUObject(this, &AKTABaseCharacter::OnHealthChanged);

    LandedDelegate.AddDynamic(this, &AKTABaseCharacter::OnGroundLanded);
}

// Called every frame
void AKTABaseCharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    // TakeDamage(0.1f, FDamageEvent{}, Controller, this);
}

void AKTABaseCharacter::TurnOff()
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::TurnOff();
}

void AKTABaseCharacter::Reset()
{
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);
    Super::Reset();
}

// Called to bind functionality to input




float AKTABaseCharacter::GetMovementDirection() const
{
    if (GetVelocity().IsZero())
        return 0.0f;
    const auto VelocityNormal = GetVelocity().GetSafeNormal();
    const auto AngleBetween = FMath::Acos(FVector::DotProduct(GetActorForwardVector(), VelocityNormal));
    const auto CrossProduct = FVector::CrossProduct(GetActorForwardVector(), VelocityNormal);
    const auto Degrees = FMath::RadiansToDegrees(AngleBetween);

    return CrossProduct.IsZero() ? Degrees : Degrees * FMath::Sign(CrossProduct.Z);
}

void AKTABaseCharacter::SetPlayerColor(const FLinearColor &Color)
{
    const auto MaterialInst = GetMesh()->CreateAndSetMaterialInstanceDynamic(0);
    if (!MaterialInst)
        return;

    MaterialInst->SetVectorParameterValue(MaterialColorName, Color);
}

bool AKTABaseCharacter::IsRunning() const
{
    return false;
}

void AKTABaseCharacter::OnDeath()
{
    UE_LOG(BaseCharacterLog, Display, TEXT("Player % s is dead"), *GetName());
    //PlayAnimMontage(DeathAnimMontage);

    GetCharacterMovement()->DisableMovement();
    SetLifeSpan(LifeSpanOnDeath);

    GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Ignore);
    if (!WeaponComponent)
        return;
    WeaponComponent->StopFire();
    WeaponComponent->Zoom(false);

    GetMesh()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
    GetMesh()->SetSimulatePhysics(true);

    UGameplayStatics::PlaySoundAtLocation(GetWorld(), DeathSound, GetActorLocation());
}

void AKTABaseCharacter::OnHealthChanged(float Health, float HealthDelta)
{
    
}

void AKTABaseCharacter::OnGroundLanded(const FHitResult &Hit)
{
    const auto FallVelocityZ = -GetVelocity().Z;
    UE_LOG(BaseCharacterLog, Display, TEXT("On landed: %f"), FallVelocityZ);
    if (FallVelocityZ < LandedDamageVelocity.X)
        return;

    const auto FinalDagame = FMath::GetMappedRangeValueClamped(LandedDamageVelocity, LandedDamage, FallVelocityZ);
    TakeDamage(FinalDagame, FDamageEvent{}, nullptr, nullptr);
}


