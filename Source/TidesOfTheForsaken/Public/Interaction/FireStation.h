#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ShipInteractable.h"
#include "Ship/ShipFireModel.h"
#include "FireStation.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShipActor;

/** A shipboard bucket point for manually fighting one nearby fire zone. */
UCLASS()
class TIDESOFTHEFORSAKEN_API AFireStation : public AActor, public IShipInteractable
{
    GENERATED_BODY()

public:
    AFireStation();
    void Configure(AShipActor* Ship, Tides::Fire::EZone InZone);
    virtual bool CanInteract(const ACaptainCharacter* Captain) const override;
    virtual FText GetInteractionText() const override;
    virtual void Interact(ACaptainCharacter* Captain) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Fire")
    TObjectPtr<UBoxComponent> InteractionBounds;

    UPROPERTY(VisibleAnywhere, Category="Fire")
    TObjectPtr<UStaticMeshComponent> BucketVisual;

    UPROPERTY()
    TObjectPtr<AShipActor> OwningShip;

    Tides::Fire::EZone Zone = Tides::Fire::EZone::Deck;
};
