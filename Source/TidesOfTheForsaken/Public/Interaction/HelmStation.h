#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ShipInteractable.h"
#include "HelmStation.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShipActor;

/** A traceable wheel that stays attached to the moving ship. */
UCLASS()
class TIDESOFTHEFORSAKEN_API AHelmStation : public AActor, public IShipInteractable
{
    GENERATED_BODY()

public:
    AHelmStation();
    void SetOwningShip(AShipActor* Ship);
    virtual bool CanInteract(const ACaptainCharacter* Captain) const override;
    virtual FText GetInteractionText() const override;
    virtual void Interact(ACaptainCharacter* Captain) override;

private:
    UPROPERTY(VisibleAnywhere, Category="Interaction")
    TObjectPtr<UBoxComponent> InteractionBounds;

    UPROPERTY(VisibleAnywhere, Category="Interaction")
    TObjectPtr<UStaticMeshComponent> WheelVisual;

    UPROPERTY()
    TObjectPtr<AShipActor> OwningShip;
};
