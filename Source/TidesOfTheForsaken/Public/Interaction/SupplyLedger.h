#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ShipInteractable.h"
#include "SupplyLedger.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShipActor;

/** Physical hold ledger exposing the ship's actual supply inventory. */
UCLASS()
class TIDESOFTHEFORSAKEN_API ASupplyLedger : public AActor, public IShipInteractable
{
    GENERATED_BODY()

public:
    ASupplyLedger();
    void SetOwningShip(AShipActor* Ship);
    virtual bool CanInteract(const ACaptainCharacter* Captain) const override;
    virtual FText GetInteractionText() const override;
    virtual void Interact(ACaptainCharacter* Captain) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Supplies")
    TObjectPtr<UBoxComponent> InteractionBounds;

    UPROPERTY(VisibleAnywhere, Category="Supplies")
    TObjectPtr<UStaticMeshComponent> LedgerVisual;

    UPROPERTY()
    TObjectPtr<AShipActor> OwningShip;
};
