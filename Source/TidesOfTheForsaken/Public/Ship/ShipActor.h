#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShipActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UShipMovementComponent;
class UShipCommandComponent;
class UShipDamageComponent;
class UShipInventoryComponent;
class UShipCrewComponent;

/** Walkable two-level prototype ship with an open stairwell. */
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

    FVector GetCannonLocation(float AlongShip, bool bPort) const;
    FVector GetRepairStationLocation() const;

    void SetCaptainSteering(bool bSteering);
    void SetHelmRudder(float Value);
    bool IsCaptainSteering() const;

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipCommandComponent* GetShipCommands() const { return ShipCommands; }

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipDamageComponent* GetShipDamage() const { return ShipDamage; }

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipInventoryComponent* GetShipInventory() const { return ShipInventory; }

    UFUNCTION(BlueprintPure, Category="Ship")
    UShipCrewComponent* GetShipCrew() const { return ShipCrew; }

private:
    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<USceneComponent> ShipRoot;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<USceneComponent> DeckOrigin;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TArray<TObjectPtr<UStaticMeshComponent>> StructurePieces;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UStaticMeshComponent> MastVisual;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipMovementComponent> ShipMovement;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipCommandComponent> ShipCommands;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipDamageComponent> ShipDamage;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipInventoryComponent> ShipInventory;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipCrewComponent> ShipCrew;
};
