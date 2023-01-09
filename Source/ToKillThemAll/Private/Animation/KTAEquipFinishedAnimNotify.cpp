// Kill Them All Game, All Rights Reserved


#include "Animation/KTAEquipFinishedAnimNotify.h"


void UKTAEquipFinishedAnimNotify::Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation)
{
    OnNotified.Broadcast(MeshComp);
    Super::Notify(MeshComp, Animation);


}
