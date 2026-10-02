#include "Interaction/RepairStation.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipDamageComponent.h"
#include "Ship/ShipInventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

ARepairStation::ARepairStation()
{
    InteractionBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBounds"));
    SetRootComponent(InteractionBounds);
    InteractionBounds->SetBoxExtent(FVector(75.f, 75.f, 90.f));
    InteractionBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBounds->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    PumpVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PumpVisual"));
    PumpVisual->SetupAttachment(InteractionBounds);
    PumpVisual->SetRelativeScale3D(FVector(1.1f, 0.6f, 1.4f));
    PumpVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) PumpVisual->SetStaticMesh(Cube.Object);
}

void ARepairStation::SetOwningShip(AShipActor* Ship)
{
    OwningShip = Ship;
}

bool ARepairStation::CanInteract(const ACaptainCharacter* Captain) const
{
    return IsValid(OwningShip) && IsValid(Captain)
        && FVector::DistSquared(Captain->GetActorLocation(), GetActorLocation()) <= FMath::Square(260.f);
}

FText ARepairStation::GetInteractionText() const
{
    if (!IsValid(OwningShip)) return FText::GetEmpty();
    const UShipDamageComponent* Damage = OwningShip->GetShipDamage();
    if (Damage->GetBreachSeverity() > 0.f || Damage->GetHullIntegrity() < 100.f) return NSLOCTEXT("Tides", "PatchHull", "Patch Hull");
    if (Damage->GetWaterLevel() > 0.f) return NSLOCTEXT("Tides", "PumpBilge", "Pump Bilge");
    return NSLOCTEXT("Tides", "InspectBilge", "Inspect Bilge");
}

void ARepairStation::Interact(ACaptainCharacter* Captain)
{
    if (!CanInteract(Captain)) return;
    UShipDamageComponent* Damage = OwningShip->GetShipDamage();
    FString Message;
    if (Damage->GetBreachSeverity() > 0.f || Damage->GetHullIntegrity() < 100.f)
    {
        const bool bRepaired = Damage->RepairHull(10.f);
        Message = bRepaired ? TEXT("Hull repaired with planks") : TEXT("No planks available");
    }
    else if (Damage->GetWaterLevel() > 0.f)
    {
        Damage->PumpWater(10.f);
        Message = TEXT("Bilge pumped");
    }
    else
    {
        Message = TEXT("Bilge dry; hull sound");
    }
    if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Green, Message);
}
