#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

class USceneComponent;
class UBoxComponent;
class UStaticMeshComponent;
class UShipMovementComponent;

/** Collision-ready prototype ship. Art meshes can replace the primitive visuals. */
UCLASS()
class TIDESOFTHEFORSAKEN_API AShipActor : public AActor
{
    GENERATED_BODY()

public:
    AShipActor();
    virtual void Tick(float DeltaSeconds) override;

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipMovementComponent* GetShipMovement() const { return ShipMovement; }

    UFUNCTION(BlueprintPure, Category="Ship")
    FVector GetCaptainStartLocation() const;

    UFUNCTION(BlueprintPure, Category="Ship")
    FVector GetHelmLocation() const;

    void SetCaptainSteering(bool bSteering);
    void SetHelmRudder(float Value);
    bool IsCaptainSteering() const { return bCaptainSteering; }

private:
    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<USceneComponent> ShipRoot;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UBoxComponent> DeckCollision;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UStaticMeshComponent> HullVisual;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UStaticMeshComponent> MastVisual;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipMovementComponent> ShipMovement;

    bool bCaptainSteering = false;
    float HeldHeading = 0.f;
};
