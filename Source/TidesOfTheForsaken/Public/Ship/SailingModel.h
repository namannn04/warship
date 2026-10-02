#pragma once

// Deliberately independent of Unreal: the sailing rules can be tested with a
// normal C++ compiler before being integrated with CharacterMovement.
#include <algorithm>
#include <cmath>

namespace Tides::Sailing
{
struct FConfig
{
    double MaximumSpeed = 450.0;
    double Acceleration = 35.0;
    double Deceleration = 55.0;
    double MaximumTurnDegreesPerSecond = 8.0;
    double WaveHeight = 22.0;
    double WindX = 1.0;
    double WindY = 0.0;
};

struct FCommand
{
    double SailPower = 0.45;
    double Rudder = 0.0;
    bool bAnchored = false;
};

struct FState
{
    double X = 0.0;
    double Y = 0.0;
    double YawDegrees = 0.0;
    double Speed = 0.0;
    double Time = 0.0;
    double Heave = 0.0;
    double PitchDegrees = 0.0;
    double RollDegrees = 0.0;
};

inline double Clamp(double Value, double Minimum, double Maximum)
{
    return std::max(Minimum, std::min(Value, Maximum));
}

inline void Advance(FState& State, const FConfig& Config, const FCommand& Command, double DeltaSeconds)
{
    // Substep slow frames so the helm does not jump or lose most of a frame.
    double Remaining = Clamp(DeltaSeconds, 0.0, 0.25);
    constexpr double Pi = 3.14159265358979323846;
    while (Remaining > 0.000001)
    {
        const double Step = std::min(Remaining, 0.05);
        Remaining -= Step;
        State.Time += Step;

        const double YawRadians = State.YawDegrees * Pi / 180.0;
        const double ForwardX = std::cos(YawRadians);
        const double ForwardY = std::sin(YawRadians);
        const double WindLength = std::hypot(Config.WindX, Config.WindY);
        const double WindAlignment = WindLength > 0.000001
            ? (ForwardX * Config.WindX + ForwardY * Config.WindY) / WindLength : 0.0;
        const double WindEfficiency = Clamp(0.45 + 0.55 * WindAlignment, 0.12, 1.0);
        const double TargetSpeed = Command.bAnchored ? 0.0
            : Clamp(Command.SailPower, 0.0, 1.0) * std::max(0.0, Config.MaximumSpeed) * WindEfficiency;
        const double Rate = TargetSpeed > State.Speed ? Config.Acceleration : Config.Deceleration;
        const double SpeedDelta = Clamp(TargetSpeed - State.Speed, -Rate * Step, Rate * Step);
        State.Speed = std::max(0.0, State.Speed + SpeedDelta);

        const double SteeringAuthority = Clamp(State.Speed / 180.0, 0.0, 1.0);
        State.YawDegrees += Clamp(Command.Rudder, -1.0, 1.0)
            * Config.MaximumTurnDegreesPerSecond * SteeringAuthority * Step;
        const double NewYaw = State.YawDegrees * Pi / 180.0;
        State.X += std::cos(NewYaw) * State.Speed * Step;
        State.Y += std::sin(NewYaw) * State.Speed * Step;
        State.Heave = Config.WaveHeight * std::sin(State.Time * 0.72);
        State.PitchDegrees = 1.2 * std::sin(State.Time * 0.8);
        State.RollDegrees = 1.5 * std::sin(State.Time * 0.63 + 0.8);
    }
}
} // namespace Tides::Sailing
