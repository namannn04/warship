#include "Interaction/FireStation.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipFireComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

AFireStation::AFireStation()
{
    InteractionBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBounds"));
    SetRootComponent(InteractionBounds);
    InteractionBounds->SetBoxExtent(FVector(45.f, 45.f, 55.f));
    InteractionBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBounds->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    BucketVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BucketVisual"));
    BucketVisual->SetupAttachment(InteractionBounds);
    BucketVisual->SetRelativeScale3D(FVector(0.6f, 0.6f, 0.7f));
    BucketVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) BucketVisual->SetStaticMesh(Cube.Object);
}

void AFireStation::Configure(AShipActor* Ship, Tides::Fire::EZone InZone)
{
    OwningShip = Ship;
    Zone = InZone;
}

bool AFireStation::CanInteract(const ACaptainCharacter* Captain) const
{
    if (!IsValid(OwningShip) || !IsValid(Captain) ||
        FVector::DistSquared(Captain->GetActorLocation(), GetActorLocation()) > FMath::Square(260.f)) return false;
    const UShipFireComponent* Fire = OwningShip->GetShipFire();
    switch (Zone)
    {
    case Tides::Fire::EZone::Deck: return Fire->GetDeckFire() > 0.f;
    case Tides::Fire::EZone::Sails: return Fire->GetSailFire() > 0.f;
    case Tides::Fire::EZone::Hold: return Fire->GetHoldFire() > 0.f;
    default: return false;
    }
}

FText AFireStation::GetInteractionText() const
{
    switch (Zone)
    {
    case Tides::Fire::EZone::Deck: return NSLOCTEXT("Tides", "FightDeckFire", "Fight Deck Fire");
    case Tides::Fire::EZone::Sails: return NSLOCTEXT("Tides", "FightSailFire", "Fight Sail Fire");
    case Tides::Fire::EZone::Hold: return NSLOCTEXT("Tides", "FightHoldFire", "Fight Hold Fire");
    default: return FText::GetEmpty();
    }
}

void AFireStation::Interact(ACaptainCharacter* Captain)
{
    if (!CanInteract(Captain)) return;
    OwningShip->GetShipFire()->Extinguish(Zone, 35.f);
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Orange, TEXT("Fire suppressed"));
}
