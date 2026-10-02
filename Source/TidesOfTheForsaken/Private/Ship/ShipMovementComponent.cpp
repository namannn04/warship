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

void UShipMovementComponent::SetConditionFactors(float SailFactor, float RudderFactor, float NewWaterLevel)
{
    SailCondition = FMath::Clamp(SailFactor, 0.f, 1.f);
    RudderCondition = FMath::Clamp(RudderFactor, 0.f, 1.f);
    WaterLevel = FMath::Clamp(NewWaterLevel, 0.f, 100.f);
}

void UShipMovementComponent::SetWeather(float WindHeadingDegrees, float NewWaveHeightCm, float WindSpeedFactor)
{
    const float Radians = FMath::DegreesToRadians(WindHeadingDegrees);
    WindDirection = FVector(FMath::Cos(Radians), FMath::Sin(Radians), 0.f);
    WaveHeightCm = FMath::Max(0.f, NewWaveHeightCm);
    WeatherSpeedFactor = FMath::Clamp(WindSpeedFactor, 0.1f, 2.f);
}

void UShipMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
    Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
    if (!GetOwner() || DeltaTime <= 0.f) return;

    Tides::Sailing::FConfig Config;
    Config.MaximumSpeed = MaximumSpeedCmPerSecond * SailCondition * WeatherSpeedFactor;
    Config.Acceleration = AccelerationCmPerSecondSquared;
    Config.Deceleration = DecelerationCmPerSecondSquared;
    Config.MaximumTurnDegreesPerSecond = MaximumTurnDegreesPerSecond * RudderCondition;
    Config.WaveHeight = WaveHeightCm;
    Config.WindX = WindDirection.X;
    Config.WindY = WindDirection.Y;

    Tides::Sailing::FCommand Command;
    Command.SailPower = SailPower;
    Command.Rudder = Rudder;
    Command.bAnchored = bAnchored;
    Tides::Sailing::Advance(SailingState, Config, Command, DeltaTime);
    SpeedCmPerSecond = static_cast<float>(SailingState.Speed);

    const FVector Position(SailingState.X, SailingState.Y, BaseWaterlineZ + SailingState.Heave - WaterLevel * 1.5f);
    const FRotator Rotation(SailingState.PitchDegrees, SailingState.YawDegrees, SailingState.RollDegrees);
    GetOwner()->SetActorLocationAndRotation(Position, Rotation, false, nullptr, ETeleportType::None);
}
