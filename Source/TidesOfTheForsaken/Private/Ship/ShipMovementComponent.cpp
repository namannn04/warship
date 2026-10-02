#include "Ship/ShipMovementComponent.h"
#include "GameFramework/Actor.h"

UShipMovementComponent::UShipMovementComponent()
{
    PrimaryComponentTick.bCanEverTick = true;
    PrimaryComponentTick.TickGroup = TG_PrePhysics;
}

void UShipMovementComponent::BeginPlay()
{
    Super::BeginPlay();
    BaseWaterlineZ = GetOwner()->GetActorLocation().Z;
    WindDirection = WindDirection.GetSafeNormal2D();
}

void UShipMovementComponent::SetSailPower(float Value)
{
    SailPower = FMath::Clamp(Value, 0.f, 1.f);
}

void UShipMovementComponent::SetRudder(float Value)
{
    Rudder = FMath::Clamp(Value, -1.f, 1.f);
}

void UShipMovementComponent::SetAnchored(bool bValue)
{
    bAnchored = bValue;
}

void UShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!GetOwner() || DeltaTime <= 0.f) return;

    const float Step = FMath::Min(DeltaTime, 0.05f);
    SimulationTime += Step;
    const FVector Forward = GetOwner()->GetActorForwardVector();
    const float WindAlignment = FVector::DotProduct(Forward, WindDirection);
    // Sailing into the wind remains possible at low speed; broad reach is faster.
    const float WindEfficiency = FMath::Clamp(0.45f + 0.55f * WindAlignment, 0.12f, 1.f);
    const float TargetSpeed = bAnchored ? 0.f : SailPower * MaximumSpeedCmPerSecond * WindEfficiency;
    const float Rate = TargetSpeed > SpeedCmPerSecond ? AccelerationCmPerSecondSquared : DecelerationCmPerSecondSquared;
    SpeedCmPerSecond = FMath::FInterpConstantTo(SpeedCmPerSecond, TargetSpeed, Step, Rate);

    const float SteeringAuthority = FMath::Clamp(SpeedCmPerSecond / 180.f, 0.f, 1.f);
    const float YawDelta = Rudder * MaximumTurnDegreesPerSecond * SteeringAuthority * Step;
    FRotator Rotation = GetOwner()->GetActorRotation();
    Rotation.Yaw = FRotator::NormalizeAxis(Rotation.Yaw + YawDelta);
    Rotation.Pitch = 1.2f * FMath::Sin(SimulationTime * 0.8f);
    Rotation.Roll = 1.5f * FMath::Sin(SimulationTime * 0.63f + 0.8f);

    FVector Position = GetOwner()->GetActorLocation() + Forward * SpeedCmPerSecond * Step;
    Position.Z = BaseWaterlineZ + WaveHeightCm * FMath::Sin(SimulationTime * 0.72f);
    GetOwner()->SetActorLocationAndRotation(Position, Rotation, false, nullptr, ETeleportType::None);
}
