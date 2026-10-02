#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ship/ShipInventoryModel.h"
#include "ShipInventoryComponent.generated.h"

/** Supply ownership for one ship; stations and crew consume from here. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipInventoryComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    bool ConsumePlanks(int32 Count) { return Tides::Inventory::ConsumePlanks(Supplies, Count); }
    bool ConsumePowder() { return Tides::Inventory::ConsumePowder(Supplies); }
    bool ConsumeCannonball() { return Tides::Inventory::ConsumeCannonball(Supplies); }

    UFUNCTION(BlueprintPure, Category="Ship|Supplies")
    int32 GetPlanks() const { return Supplies.Planks; }

    UFUNCTION(BlueprintPure, Category="Ship|Supplies")
    int32 GetPowderCharges() const { return Supplies.PowderCharges; }

    UFUNCTION(BlueprintPure, Category="Ship|Supplies")
    int32 GetCannonballs() const { return Supplies.Cannonballs; }

    UFUNCTION(BlueprintPure, Category="Ship|Supplies")
    int32 GetFoodRations() const { return Supplies.FoodRations; }

    float GetCargoSpeedFactor() const { return static_cast<float>(Tides::Inventory::CargoSpeedFactor(Supplies)); }

private:
    Tides::Inventory::FState Supplies;
};
