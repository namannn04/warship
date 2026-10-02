#include "Ship/ShipDamageComponent.h"
#include "Ship/ShipMovementComponent.h"
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

void UShipDamageComponent::RepairHull(float Work)
{
    Tides::Damage::RepairHull(Condition, Work);
}

void UShipDamageComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    Tides::Damage::Tick(Condition, DeltaTime, bPumping);
    if (UShipMovementComponent* Movement = GetOwner()->FindComponentByClass<UShipMovementComponent>())
    {
        Movement->SetConditionFactors(static_cast<float>(Tides::Damage::SailEfficiency(Condition)),
            static_cast<float>(Tides::Damage::RudderEfficiency(Condition)),
            static_cast<float>(Condition.Water));
        if (Condition.bSunk) Movement->SetSailPower(0.f);
    }
}
