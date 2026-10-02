#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

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

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipMovementComponent* GetShipMovement() const { return ShipMovement; }

    UFUNCTION(BlueprintPure, Category="Ship")
    FVector GetCaptainStartLocation() const;

    UFUNCTION(BlueprintPure, Category="Ship")
    FVector GetHelmLocation() const;

private:
    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UBoxComponent> DeckCollision;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UStaticMeshComponent> HullVisual;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UStaticMeshComponent> MastVisual;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipMovementComponent> ShipMovement;
};
