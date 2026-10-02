#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ship/ShipFireModel.h"
#include "ShipActor.generated.h"

class USceneComponent;
class UStaticMeshComponent;
class UShipMovementComponent;
class UShipCommandComponent;
class UShipDamageComponent;
class UShipInventoryComponent;
class UShipCrewComponent;
class UShipFireComponent;
class UPointLightComponent;
class UEnemyShipAIComponent;

/** Walkable three-level prototype ship with open stairwells and an aft cabin. */
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
    FVector GetGunDeckCrewLocation(float AlongShip, float AcrossShip) const;
    FVector GetSupplyLedgerLocation() const;
    FVector GetFireStationLocation(Tides::Fire::EZone Zone) const;

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

    UShipFireComponent* GetShipFire() const { return ShipFire; }
    UEnemyShipAIComponent* GetEnemyAI() const { return EnemyAI; }
    void SetFireVisuals(float DeckHeat, float SailHeat, float HoldHeat);

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

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UShipFireComponent> ShipFire;

    UPROPERTY(VisibleAnywhere, Category="Ship")
    TObjectPtr<UEnemyShipAIComponent> EnemyAI;

    UPROPERTY(VisibleAnywhere, Category="Ship|Fire")
    TObjectPtr<UPointLightComponent> DeckFireLight;

    UPROPERTY(VisibleAnywhere, Category="Ship|Fire")
    TObjectPtr<UPointLightComponent> SailFireLight;

    UPROPERTY(VisibleAnywhere, Category="Ship|Fire")
    TObjectPtr<UPointLightComponent> HoldFireLight;
};
