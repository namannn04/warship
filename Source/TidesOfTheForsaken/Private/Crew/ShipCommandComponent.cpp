#include "Crew/ShipCommandComponent.h"
#include "Ship/ShipMovementComponent.h"
#include "Ship/SailingModel.h"
#include "GameFramework/Actor.h"

UShipCommandComponent::UShipCommandComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UShipCommandComponent::BeginPlay()
{
    Super::BeginPlay();
    Movement = GetOwner()->FindComponentByClass<UShipMovementComponent>();
    OrderedHeading = GetOwner()->GetActorRotation().Yaw;
    if (Movement) Movement->AddTickPrerequisiteComponent(this);
}

void UShipCommandComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!Movement || bCaptainAtHelm) return;
    Movement->SetRudder(static_cast<float>(Tides::Sailing::RudderForHeading(
        GetOwner()->GetActorRotation().Yaw, OrderedHeading)));
}

void UShipCommandComponent::SetCaptainAtHelm(bool bValue)
{
    bCaptainAtHelm = bValue;
    if (!bValue) OrderHoldHeading();
}

void UShipCommandComponent::OrderSailPower(float Power)
{
    if (Movement) Movement->SetSailPower(Power);
}

void UShipCommandComponent::OrderTurn(float Degrees)
{
    OrderedHeading = FRotator::NormalizeAxis(OrderedHeading + FMath::Clamp(Degrees, -90.f, 90.f));
}

void UShipCommandComponent::OrderHoldHeading()
{
    OrderedHeading = GetOwner()->GetActorRotation().Yaw;
}

void UShipCommandComponent::OrderAnchorToggle()
{
    if (Movement) Movement->SetAnchored(!Movement->IsAnchored());
}
