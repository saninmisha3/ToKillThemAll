#pragma once
#include "Player/KTAPlayerState.h"



class KTAUtils
{
  public:
    template <typename T> static T *GetKTAPlayerComponent(AActor *PlayerPawn)
    {
        if (!PlayerPawn)
            return nullptr;

        const auto Component = PlayerPawn->GetComponentByClass(T::StaticClass());
        return Cast<T>(Component);
    }

    bool static AreEnemies(AController *Controller1, AController *Controller2)
    {
        if (!Controller1 || !Controller2 || Controller1 == Controller2)
            return false;

        const auto PlayerState1 = Cast<AKTAPlayerState>(Controller1->PlayerState);
        const auto PlayerState2 = Cast<AKTAPlayerState>(Controller2->PlayerState);

        return PlayerState1 && PlayerState2 && PlayerState1->GetTeamID() != PlayerState2->GetTeamID();
    }
};