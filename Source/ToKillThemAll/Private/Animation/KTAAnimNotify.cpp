// Kill Them All Game, All Rights Reserved


#include "Animation/KTAAnimNotify.h"

void UKTAAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);
}