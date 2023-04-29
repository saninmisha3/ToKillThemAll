// Kill Them All Game, All Rights Reserved


#include "KTAPlayerController.h"
#include "Components/KTARespawnComponent.h"
#include "KTAGameModeBase.h"


AKTAPlayerController::AKTAPlayerController()
{
    RespawnComponent = CreateDefaultSubobject<UKTARespawnComponent>("RespawnComponent");
}

void AKTAPlayerController::SetupInputComponent() 
{
    Super::SetupInputComponent();
    if (!InputComponent)
        return;

    InputComponent->BindAction("PauseGame", IE_Pressed, this, &AKTAPlayerController::OnPauseDame);
}

void AKTAPlayerController::OnPauseDame()
{
    if (!GetWorld() || !GetWorld()->GetAuthGameMode())
        return;

    GetWorld()->GetAuthGameMode()->SetPause(this);
}

void AKTAPlayerController::BeginPlay()
{
    Super::BeginPlay();

    if (GetWorld())
    {
        const auto GameMode = Cast<AKTAGameModeBase>(GetWorld()->GetAuthGameMode());
        if (GameMode)
        {
            GameMode->OnMatchSatateChanged.AddUObject(this, &AKTAPlayerController::OnMatchStateChanged);
        }
    }
}

void AKTAPlayerController::OnMatchStateChanged(EKTAMatchState State)
{
    if (State == EKTAMatchState::InProgress)
    {
        SetInputMode(FInputModeGameOnly());
        bShowMouseCursor = false;
    }
    else
    {
        SetInputMode(FInputModeUIOnly());
        bShowMouseCursor = true;
    }
}