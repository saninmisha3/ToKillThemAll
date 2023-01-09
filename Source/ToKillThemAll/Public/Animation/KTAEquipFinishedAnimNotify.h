// Kill Them All Game, All Rights Reserved

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "KTAEquipFinishedAnimNotify.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnNotifiedSignature, USkeletalMeshComponent*);

/**
 * 
 */
UCLASS()
class TOKILLTHEMALL_API UKTAEquipFinishedAnimNotify : public UAnimNotify
{
	GENERATED_BODY()
	

		public: 
		virtual void Notify(USkeletalMeshComponent *MeshComp, UAnimSequenceBase *Animation) override;

		FOnNotifiedSignature OnNotified;

};
