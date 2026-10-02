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
    SailingState.X = GetOwner()->GetActorLocation().X;
    SailingState.Y = GetOwner()->GetActorLocation().Y;
    SailingState.YawDegrees = GetOwner()->GetActorRotation().Yaw;
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

    Tides::Sailing::FConfig Config;
    Config.MaximumSpeed = MaximumSpeedCmPerSecond;
    Config.Acceleration = AccelerationCmPerSecondSquared;
    Config.Deceleration = DecelerationCmPerSecondSquared;
    Config.MaximumTurnDegreesPerSecond = MaximumTurnDegreesPerSecond;
    Config.WaveHeight = WaveHeightCm;
    Config.WindX = WindDirection.X;
    Config.WindY = WindDirection.Y;

    Tides::Sailing::FCommand Command;
    Command.SailPower = SailPower;
    Command.Rudder = Rudder;
    Command.bAnchored = bAnchored;
    Tides::Sailing::Advance(SailingState, Config, Command, DeltaTime);
    SpeedCmPerSecond = static_cast<float>(SailingState.Speed);

    const FVector Position(SailingState.X, SailingState.Y, BaseWaterlineZ + SailingState.Heave);
    const FRotator Rotation(SailingState.PitchDegrees, SailingState.YawDegrees, SailingState.RollDegrees);
    GetOwner()->SetActorLocationAndRotation(Position, Rotation, false, nullptr, ETeleportType::None);
}
