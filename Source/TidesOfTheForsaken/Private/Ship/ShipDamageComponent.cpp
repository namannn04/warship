#include "Ship/ShipDamageComponent.h"
#include "Ship/ShipMovementComponent.h"
#include "Ship/ShipInventoryComponent.h"
#include "Components/PrimitiveComponent.h"
#include "GameFramework/Actor.h"

UShipDamageComponent::UShipDamageComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
}

void UShipDamageComponent::ApplyImpact(const UPrimitiveComponent* HitComponent, float Strength)
{
    if (!HitComponent) return;
    const FString Name = HitComponent->GetName();
    const Tides::Damage::ESection Section = Name.StartsWith(TEXT("Mast"))
        ? Tides::Damage::ESection::Mast : Tides::Damage::ESection::Hull;
    Tides::Damage::ApplyHit(Condition, Section, Strength);
}

bool UShipDamageComponent::RepairHull(float Work)
{
    if (Work <= 0.f || Condition.bSunk) return false;
    UShipInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UShipInventoryComponent>();
    const int32 PlanksNeeded = FMath::Max(1, FMath::CeilToInt(Work / 5.f));
    if (Inventory && Inventory->ConsumePlanks(PlanksNeeded))
    {
        Tides::Damage::RepairHull(Condition, Work);
        return true;
    }
    return false;
}

void UShipDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Tides::Damage::Tick(Condition, DeltaTime, bPumping);
    if (UShipMovementComponent* Movement = GetOwner()->FindComponentByClass<UShipMovementComponent>())
    {
        const UShipInventoryComponent* Inventory = GetOwner()->FindComponentByClass<UShipInventoryComponent>();
        const float CargoFactor = Inventory ? Inventory->GetCargoSpeedFactor() : 1.f;
        Movement->SetConditionFactors(static_cast<float>(Tides::Damage::SailEfficiency(Condition)) * CargoFactor,
            static_cast<float>(Tides::Damage::RudderEfficiency(Condition)),
            static_cast<float>(Condition.Water));
        if (Condition.bSunk) Movement->SetSailPower(0.f);
    }
}
