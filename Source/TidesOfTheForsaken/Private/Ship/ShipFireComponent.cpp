#include "Ship/ShipFireComponent.h"
#include "Ship/ShipActor.h"
#include "Ship/ShipDamageComponent.h"

UShipFireComponent::UShipFireComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UShipFireComponent::SetWeather(float InWind, float InRain)
{
    Wind = FMath::Clamp(InWind, 0.f, 1.f);
    Rain = FMath::Clamp(InRain, 0.f, 1.f);
}

void UShipFireComponent::Ignite(Tides::Fire::EZone Zone, float Strength)
{
    Tides::Fire::Ignite(FireState, Zone, Strength);
}

bool UShipFireComponent::Extinguish(Tides::Fire::EZone Zone, float Work)
{
    if (Work <= 0.f || Tides::Fire::HeatAt(FireState, Zone) <= 0.0) return false;
    Tides::Fire::Extinguish(FireState, Zone, Work);
    return true;
}

Tides::Fire::EZone UShipFireComponent::HottestZone() const
{
    Tides::Fire::EZone Hottest = Tides::Fire::EZone::Deck;
    for (const Tides::Fire::EZone Zone : { Tides::Fire::EZone::Sails, Tides::Fire::EZone::Hold })
    {
        if (Tides::Fire::HeatAt(FireState, Zone) > Tides::Fire::HeatAt(FireState, Hottest)) Hottest = Zone;
    }
    return Hottest;
}

void UShipFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    const float Step = FMath::Clamp(DeltaTime, 0.f, 0.25f);
    Tides::Fire::Advance(FireState, Step, Wind, Rain);
    if (UShipDamageComponent* Damage = GetOwner()->FindComponentByClass<UShipDamageComponent>())
    {
        Damage->ApplyFireDamage(
            static_cast<float>(Tides::Fire::StructuralDamagePerSecond(FireState, Tides::Fire::EZone::Deck) * Step),
            static_cast<float>(Tides::Fire::StructuralDamagePerSecond(FireState, Tides::Fire::EZone::Sails) * Step),
            static_cast<float>(Tides::Fire::StructuralDamagePerSecond(FireState, Tides::Fire::EZone::Hold) * Step));
    }
    if (AShipActor* Ship = Cast<AShipActor>(GetOwner()))
    {
        Ship->SetFireVisuals(GetDeckFire(), GetSailFire(), GetHoldFire());
    }
}
