#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Interaction/ShipInteractable.h"
#include "Ship/CannonModel.h"
#include "ShipCannon.generated.h"

class UBoxComponent;
class UStaticMeshComponent;
class AShipActor;

/** A physical gun-deck cannon with a complete manual loading cycle. */
UCLASS()
class TIDESOFTHEFORSAKEN_API AShipCannon : public AActor, public IShipInteractable
{
    GENERATED_BODY()

public:
    AShipCannon();
    virtual void Tick(float DeltaSeconds) override;
    void SetOwningShip(AShipActor* Ship);
    virtual bool CanInteract(const ACaptainCharacter* Captain) const override;
    virtual FText GetInteractionText() const override;
    virtual void Interact(ACaptainCharacter* Captain) override;

    FVector GetOperatorLocation() const;
    FRotator GetAimRotation() const;
    void Aim(float YawInput, float PitchInput);
    bool AdvanceLoading();
    bool NeedsLoading() const;
    bool IsOperated() const { return bOperated; }
    void SetOperated(bool bValue) { bOperated = bValue; }
    bool Fire();
    const char* GetLoadingStageLabel() const;

private:
    UPROPERTY(VisibleAnywhere, Category="Cannon")
    TObjectPtr<UBoxComponent> InteractionBounds;

    UPROPERTY(VisibleAnywhere, Category="Cannon")
    TObjectPtr<UStaticMeshComponent> BarrelVisual;

    UPROPERTY()
    TObjectPtr<AShipActor> OwningShip;

    Tides::Cannon::FState LoadingState;
    float AimYaw = 0.f;
    float AimPitch = 0.f;
    bool bOperated = false;
};
