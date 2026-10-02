#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ship/ShipDamageModel.h"
#include "ShipDamageComponent.generated.h"

class UPrimitiveComponent;

/** Maps physical impacts to localized damage and advances flooding. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipDamageComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShipDamageComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void ApplyImpact(const UPrimitiveComponent* HitComponent, float Strength);

    UFUNCTION(BlueprintCallable, Category="Ship|Damage")
    bool RepairHull(float Work);

    UFUNCTION(BlueprintCallable, Category="Ship|Damage")
    void SetPumping(bool bValue) { bPumping = bValue; }

    UFUNCTION(BlueprintPure, Category="Ship|Damage")
    bool IsPumping() const { return bPumping; }

    UFUNCTION(BlueprintPure, Category="Ship|Damage")
    float GetHullIntegrity() const { return static_cast<float>(Condition.Hull); }

    UFUNCTION(BlueprintPure, Category="Ship|Damage")
    float GetWaterLevel() const { return static_cast<float>(Condition.Water); }

    UFUNCTION(BlueprintPure, Category="Ship|Damage")
    bool IsSunk() const { return Condition.bSunk; }

private:
    Tides::Damage::FState Condition;
    bool bPumping = false;
};
