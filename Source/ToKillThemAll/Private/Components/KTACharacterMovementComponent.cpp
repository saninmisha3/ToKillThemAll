// Kill Them All Game, All Rights Reserved


#include "Components/KTACharacterMovementComponent.h"
#include "KTABaseCharacter.h"

float UKTACharacterMovementComponent::GetMaxSpeed() const
{
    const float MaxSpeed = Super::GetMaxSpeed();
    const AKTABaseCharacter *Player = Cast<AKTABaseCharacter>(GetPawnOwner());
    return Player && Player->IsRunning() ? MaxSpeed * RunModifier : MaxSpeed;
}