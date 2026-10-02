#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Ship/ShipFireModel.h"
#include "ShipFireComponent.generated.h"

/** Ship-local fire state; the weather director supplies wind and rain. */
UCLASS(ClassGroup=(Ship), meta=(BlueprintSpawnableComponent))
class TIDESOFTHEFORSAKEN_API UShipFireComponent : public UActorComponent
{
    GENERATED_BODY()

public:
    UShipFireComponent();
    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    void SetWeather(float InWind, float InRain);
    void Ignite(Tides::Fire::EZone Zone, float Strength);
    bool Extinguish(Tides::Fire::EZone Zone, float Work);
    Tides::Fire::EZone HottestZone() const;

    UFUNCTION(BlueprintPure, Category="Ship|Fire")
    float GetDeckFire() const { return static_cast<float>(Tides::Fire::HeatAt(FireState, Tides::Fire::EZone::Deck)); }

    UFUNCTION(BlueprintPure, Category="Ship|Fire")
    float GetSailFire() const { return static_cast<float>(Tides::Fire::HeatAt(FireState, Tides::Fire::EZone::Sails)); }

    UFUNCTION(BlueprintPure, Category="Ship|Fire")
    float GetHoldFire() const { return static_cast<float>(Tides::Fire::HeatAt(FireState, Tides::Fire::EZone::Hold)); }

private:
    Tides::Fire::FState FireState;
    float Wind = 0.f;
    float Rain = 0.f;
};
