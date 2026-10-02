#include "Combat/ShipCannon.h"
#include "Combat/Cannonball.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipInventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/World.h"
#include "UObject/ConstructorHelpers.h"

AShipCannon::AShipCannon()
{
    PrimaryActorTick.bCanEverTick = true;
    InteractionBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBounds"));
    SetRootComponent(InteractionBounds);
    InteractionBounds->SetBoxExtent(FVector(105.f, 60.f, 70.f));
    InteractionBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBounds->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    BarrelVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BarrelVisual"));
    BarrelVisual->SetupAttachment(InteractionBounds);
    BarrelVisual->SetRelativeScale3D(FVector(1.9f, 0.55f, 0.55f));
    BarrelVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) BarrelVisual->SetStaticMesh(Cube.Object);
}

void AShipCannon::SetOwningShip(AShipActor* Ship)
{
    OwningShip = Ship;
}

bool AShipCannon::CanInteract(const ACaptainCharacter* Captain) const
{
    return IsValid(OwningShip) && IsValid(Captain)
        && FVector::DistSquared(Captain->GetActorLocation(), GetActorLocation()) < FMath::Square(280.f);
}

FText AShipCannon::GetInteractionText() const
{
    return NSLOCTEXT("Tides", "OperateCannon", "Operate Cannon");
}

void AShipCannon::Interact(ACaptainCharacter* Captain)
{
    if (CanInteract(Captain)) Captain->OperateCannon(this);
}

FVector AShipCannon::GetOperatorLocation() const
{
    return GetActorLocation() - GetActorForwardVector() * 145.f + FVector(0.f, 0.f, 15.f);
}

FRotator AShipCannon::GetAimRotation() const
{
    return GetActorRotation() + FRotator(AimPitch, AimYaw, 0.f);
}

void AShipCannon::Aim(float YawInput, float PitchInput)
{
    AimYaw = FMath::Clamp(AimYaw + YawInput * 0.6f, -25.f, 25.f);
    AimPitch = FMath::Clamp(AimPitch + PitchInput * 0.6f, -8.f, 15.f);
    BarrelVisual->SetRelativeRotation(FRotator(AimPitch, AimYaw, 0.f));
}

void AShipCannon::AdvanceLoading()
{
    if (!IsValid(OwningShip)) return;
    UShipInventoryComponent* Inventory = OwningShip->GetShipInventory();
    if (LoadingState.Stage == Tides::Cannon::EStage::Clean && !Inventory->ConsumePowder()) return;
    if (LoadingState.Stage == Tides::Cannon::EStage::Powder && !Inventory->ConsumeCannonball()) return;
    Tides::Cannon::AdvanceLoading(LoadingState);
}

bool AShipCannon::Fire()
{
    if (!Tides::Cannon::Fire(LoadingState)) return false;
    const FRotator ShotRotation = GetAimRotation();
    const FVector Muzzle = GetActorLocation() + ShotRotation.Vector() * 170.f + FVector(0.f, 0.f, 20.f);
    FActorSpawnParameters SpawnParameters;
    SpawnParameters.Owner = this;
    SpawnParameters.Instigator = nullptr;
    GetWorld()->SpawnActor<ACannonball>(ACannonball::StaticClass(), Muzzle, ShotRotation, SpawnParameters);
    return true;
}

const char* AShipCannon::GetLoadingStageLabel() const
{
    return Tides::Cannon::StageLabel(LoadingState.Stage);
}

void AShipCannon::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    Tides::Cannon::Tick(LoadingState, DeltaSeconds);
    const float RecoilFraction = LoadingState.Stage == Tides::Cannon::EStage::Recoil
        ? FMath::Clamp(static_cast<float>(LoadingState.RecoilRemainingSeconds / 0.8), 0.f, 1.f) : 0.f;
    BarrelVisual->SetRelativeLocation(FVector(-35.f * RecoilFraction, 0.f, 0.f));
}
