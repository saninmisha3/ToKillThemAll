// Kill Them All Game, All Rights Reserved


#include "Player/KTAPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/KTAWeaponComponent.h"
#include "Components/SphereComponent.h"
#include "Components/CapsuleComponent.h"

AKTAPlayerCharacter::AKTAPlayerCharacter(const FObjectInitializer &ObjInt) : Super(ObjInt)
{
    PrimaryActorTick.bCanEverTick = true;

    SpringArmComponent = CreateDefaultSubobject<USpringArmComponent>("SpringArmComponent");
    SpringArmComponent->SetupAttachment(GetRootComponent());
    SpringArmComponent->bUsePawnControlRotation = true;
    SpringArmComponent->SocketOffset = FVector(0.0f, 100.0f, 80.0f);

    CameraComponent = CreateDefaultSubobject<UCameraComponent>("CameraComponent");
    CameraComponent->SetupAttachment(SpringArmComponent);

    CameraCollisionComponent = CreateDefaultSubobject<USphereComponent>("CameraCollisionComponent");
    CameraCollisionComponent->SetupAttachment(CameraComponent);
    CameraCollisionComponent->SetSphereRadius(10.0f);
    CameraCollisionComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
}


void AKTAPlayerCharacter::BeginPlay()
{
    Super::BeginPlay();

    check(CameraCollisionComponent);

    CameraCollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AKTAPlayerCharacter::OnCameraCollisionBeginOverlap);
    CameraCollisionComponent->OnComponentEndOverlap.AddDynamic(this, &AKTAPlayerCharacter::OnCameraCollisionEndOverlap);
}

void AKTAPlayerCharacter::SetupPlayerInputComponent(UInputComponent *PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);

    check(WeaponComponent);
    PlayerInputComponent->BindAxis("MoveForward", this, &AKTAPlayerCharacter::MoveForward);
    PlayerInputComponent->BindAxis("MoveRight", this, &AKTAPlayerCharacter::MoveRight);
    PlayerInputComponent->BindAxis("LookUp", this, &AKTAPlayerCharacter::AddControllerPitchInput);
    PlayerInputComponent->BindAxis("TurnAround", this, &AKTAPlayerCharacter::AddControllerYawInput);
    PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &AKTAPlayerCharacter::Jump);
    PlayerInputComponent->BindAction("Run", IE_Pressed, this, &AKTAPlayerCharacter::OnStartRunning);
    PlayerInputComponent->BindAction("Run", IE_Released, this, &AKTAPlayerCharacter::OnStopRunning);
    PlayerInputComponent->BindAction("Fire", IE_Pressed, WeaponComponent, &UKTAWeaponComponent::StartFire);
    PlayerInputComponent->BindAction("Fire", IE_Released, WeaponComponent, &UKTAWeaponComponent::StopFire);
    PlayerInputComponent->BindAction("NextWeapon", IE_Released, WeaponComponent, &UKTAWeaponComponent::NextWeapon);
    PlayerInputComponent->BindAction("Reload", IE_Released, WeaponComponent, &UKTAWeaponComponent::Reload);

    DECLARE_DELEGATE_OneParam(FZoomInputSignature, bool);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Pressed, WeaponComponent,
                                                          &UKTAWeaponComponent::Zoom, true);
    PlayerInputComponent->BindAction<FZoomInputSignature>("Zoom", IE_Released, WeaponComponent,
                                                          &UKTAWeaponComponent::Zoom,false);
}

void AKTAPlayerCharacter::MoveForward(float Amount)
{
    IsMovingForward = Amount > 0.0f;
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorForwardVector(), Amount);
}

void AKTAPlayerCharacter::MoveRight(float Amount)
{
    if (Amount == 0.0f)
        return;
    AddMovementInput(GetActorRightVector(), Amount);
}

void AKTAPlayerCharacter::OnStartRunning()
{
    WantsToRun = true;
}

void AKTAPlayerCharacter::OnStopRunning()
{
    WantsToRun = false;
}

void AKTAPlayerCharacter::OnCameraCollisionBeginOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                                        UPrimitiveComponent *OtherComp, int32 OtherBodyIndex,
                                                        bool bFromSweep, const FHitResult &SweepResult)
{
    CheckCameraOverlap();

}

void AKTAPlayerCharacter::OnCameraCollisionEndOverlap(UPrimitiveComponent *OverlappedComponent, AActor *OtherActor,
                                                      UPrimitiveComponent *OtherComp, int32 OtherBodyIndex)
{
    CheckCameraOverlap();
}

void AKTAPlayerCharacter::CheckCameraOverlap()
{
    const bool HideMesh = CameraCollisionComponent->IsOverlappingComponent(GetCapsuleComponent());
    GetMesh()->SetOwnerNoSee(HideMesh);

    TArray<USceneComponent*> MeshChildren;
    GetMesh()->GetChildrenComponents(true,MeshChildren);

    for (auto MeshChild : MeshChildren)
    {
        const auto MeshChildGeomerty = Cast<UPrimitiveComponent>(MeshChild);
        if (MeshChildGeomerty)
        {
            MeshChildGeomerty->SetOwnerNoSee(HideMesh);
        }
        
    }
}

void AKTAPlayerCharacter::OnDeath()
{
    Super::OnDeath();

    if (Controller)
    {
        Controller->ChangeState(NAME_Spectating);
    }
}



bool AKTAPlayerCharacter::IsRunning() const
{
    return WantsToRun && IsMovingForward && !GetVelocity().IsZero();
}