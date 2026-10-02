#include "Interaction/SupplyLedger.h"
#include "Character/CaptainCharacter.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipInventoryComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

ASupplyLedger::ASupplyLedger()
{
    InteractionBounds = CreateDefaultSubobject<UBoxComponent>(TEXT("InteractionBounds"));
    SetRootComponent(InteractionBounds);
    InteractionBounds->SetBoxExtent(FVector(85.f, 60.f, 75.f));
    InteractionBounds->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    InteractionBounds->SetCollisionResponseToAllChannels(ECR_Ignore);
    InteractionBounds->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

    LedgerVisual = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("LedgerVisual"));
    LedgerVisual->SetupAttachment(InteractionBounds);
    LedgerVisual->SetRelativeScale3D(FVector(1.4f, 0.8f, 0.2f));
    LedgerVisual->SetCollisionEnabled(ECollisionEnabled::NoCollision);
    static ConstructorHelpers::FObjectFinder<UStaticMesh> Cube(TEXT("/Engine/BasicShapes/Cube.Cube"));
    if (Cube.Succeeded()) LedgerVisual->SetStaticMesh(Cube.Object);
}

void ASupplyLedger::SetOwningShip(AShipActor* Ship)
{
    OwningShip = Ship;
}

bool ASupplyLedger::CanInteract(const ACaptainCharacter* Captain) const
{
    return IsValid(OwningShip) && IsValid(Captain)
        && FVector::DistSquared(Captain->GetActorLocation(), GetActorLocation()) <= FMath::Square(260.f);
}

FText ASupplyLedger::GetInteractionText() const
{
    return NSLOCTEXT("Tides", "InspectSupplies", "Inspect Supplies");
}

void ASupplyLedger::Interact(ACaptainCharacter* Captain)
{
    if (!CanInteract(Captain) || !GEngine) return;
    const UShipInventoryComponent* Inventory = OwningShip->GetShipInventory();
    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Yellow,
        FString::Printf(TEXT("SUPPLIES  |  Planks: %d  |  Powder: %d  |  Shot: %d  |  Food: %d"),
            Inventory->GetPlanks(), Inventory->GetPowderCharges(),
            Inventory->GetCannonballs(), Inventory->GetFoodRations()));
}
