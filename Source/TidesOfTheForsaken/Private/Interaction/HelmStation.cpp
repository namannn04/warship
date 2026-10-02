#include "Interaction/HelmStation.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "UObject/ConstructorHelpers.h"

AHelmStation::AHelmStation()
{
    InteractionBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBounds"));
    SetRootComponent(InteractionBounds);
    InteractionBounds->SetBoxExtent(FVector(65.f, 90.f, 100.f));
    InteractionBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBounds->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    WheelVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WheelVisual"));
    WheelVisual->SetupAttachment(InteractionBounds);
    WheelVisual->SetRelativeScale3D(FVector(0.15f, 1.2f, 1.2f));
    WheelVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) WheelVisual->SetStaticMesh(Cube.Object);
}

void AHelmStation::SetOwningShip(AShipActor* Ship)
{
    OwningShip = Ship;
}

bool AHelmStation::CanInteract(const ACaptainCharacter* Captain) const
{
    return IsValid(OwningShip) && IsValid(Captain)
        && !OwningShip->IsCaptainSteering()
        && FVector::DistSquared(Captain->GetActorLocation(), GetActorLocation()) <= FMath::Square(300.f);
}

FText AHelmStation::GetInteractionText() const
{
    return NSLOCTEXT("Tides", "TakeHelm", "Take Helm");
}

void AHelmStation::Interact(ACaptainCharacter* Captain)
{
    if (CanInteract(Captain)) Captain->TakeHelm(OwningShip);
}
