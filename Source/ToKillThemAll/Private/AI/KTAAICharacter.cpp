// Kill Them All Game, All Rights Reserved


#include "AI/KTAAICharacter.h"
#include "AI/KTAAIController.h"
#include "Components/KTAAIWeaponComponent.h"
#include "Components/WidgetComponent.h"
#include "Components/KTAHealthComponent.h"
#include "BrainComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/KTAHealthBarWidget.h"

AKTAAICharacter::AKTAAICharacter(const FObjectInitializer &ObjInit):
    Super(ObjInit.SetDefaultSubobjectClass<UKTAAIWeaponComponent>("WeaponComponent"))
{
    AutoPossessAI = EAutoPossessAI::Disabled;
    AIControllerClass = AKTAAIController::StaticClass();

    bUseControllerRotationYaw = false;
    if (GetCharacterMovement())
    {
        GetCharacterMovement()->bUseControllerDesiredRotation = true;
        GetCharacterMovement()->RotationRate = FRotator(0.0f, 200.0f, 0.0f);
    }

    HealthWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("HealthWidgetComponent");
    HealthWidgetComponent->SetupAttachment(GetRootComponent());
    HealthWidgetComponent->SetWidgetSpace(EWidgetSpace::Screen);
    HealthWidgetComponent->SetDrawAtDesiredSize(true);
}

void AKTAAICharacter::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    UpdateHealthWidgetVisibility();
}

void AKTAAICharacter::BeginPlay()
{
    Super::BeginPlay();
    check(HealthWidgetComponent);
}

void AKTAAICharacter::OnDeath()
{
    Super::OnDeath();

    const auto KTAController = Cast<AKTAAIController>(Controller);
    if (KTAController && KTAController->BrainComponent)
    {
        KTAController->BrainComponent->Cleanup();
    }

}

void AKTAAICharacter::OnHealthChanged(float Health, float HealthDelta)
{
    Super::OnHealthChanged(Health, HealthDelta);
    const auto HealthBarWidget = Cast<UKTAHealthBarWidget>(HealthWidgetComponent->GetUserWidgetObject());
    if (!HealthBarWidget)
        return;

    HealthBarWidget->SetHealthPercent(HealthComponent->GetHealthPercent());
}

void AKTAAICharacter::UpdateHealthWidgetVisibility()
{
    if (!GetWorld() ||//
        !GetWorld()->GetFirstPlayerController() ||//
        !GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator())
        return;

    const auto PlayerLocation = GetWorld()->GetFirstPlayerController()->GetPawnOrSpectator()->GetActorLocation();
    const auto Distance = FVector::Distance(PlayerLocation,GetActorLocation());
    HealthWidgetComponent->SetVisibility(Distance < HealthVisibilityDistance, true);
}

