#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ShipInteractable.h"
#include "RepairStation.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShipActor;

/** Physical access point for patching breaches and pumping the bilge. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ARepairStation : public AActor, public IShipInteractable
{
    GENERATED_BODY()

public:
    ARepairStation();
    void SetOwningShip(AShipActor* Ship);
    virtual bool CanInteract(const ACaptainCharacter* Captain) const override;
    virtual FText GetInteractionText() const override;
    virtual void Interact(ACaptainCharacter* Captain) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Repair")
    TObjectPtr<UBoxComponent> InteractionBounds;

    UPROPERTY(VisibleAnywhere, Category="Repair")
    TObjectPtr<UStaticMeshComponent> PumpVisual;

    UPROPERTY()
    TObjectPtr<AShipActor> OwningShip;
};
