// Kill Them All Game, All Rights Reserved


#include "AI/KTAAIController.h"
#include "AI/KTAAICharacter.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/KTAAIPerceptionComponent.h"

AKTAAIController::AKTAAIController()
{
    KTAAIPerceptionComponent = CreateDefaultSubobject<UKTAAIPerceptionComponent>("KTAPerceptionComponent");
    SetPerceptionComponent(*KTAAIPerceptionComponent);
}

void AKTAAIController::OnPossess(APawn *InPawn)
{
    Super::OnPossess(InPawn);

    const auto KTACharacter = Cast<AKTAAICharacter>(InPawn);
    if (KTACharacter)
    {
        RunBehaviorTree(KTACharacter->BehaviorTreeAsset);
    
    }


}

void AKTAAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    const auto AimActor = GetFocusOnActor();
    SetFocus(AimActor);

}

AActor *AKTAAIController::GetFocusOnActor() const
{
    if (!GetBlackboardComponent())
    return nullptr;

    return Cast<AActor>(GetBlackboardComponent()->GetValueAsObject(FocusOnKeyName));
}
