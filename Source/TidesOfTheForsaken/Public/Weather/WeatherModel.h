#pragma once

#include <algorithm>
#include <cmath>

namespace Tides::Weather
{
struct FState
{
    double Hours = 8.0;
    double Storm = 0.0;
    double TargetStorm = 0.0;
    double ElapsedSeconds = 0.0;
};

inline void Advance(FState& State, double DeltaSeconds)
{
    // Preserve elapsed world time during slow frames while limiting each step.
    double Remaining = std::clamp(DeltaSeconds, 0.0, 5.0);
    while (Remaining > 0.000001)
    {
        const double Step = std::min(Remaining, 0.25);
        Remaining -= Step;
        State.ElapsedSeconds += Step;
        State.Hours = std::fmod(State.Hours + Step * 24.0 / 1200.0, 24.0);
        const double Delta = std::clamp(State.TargetStorm - State.Storm, -Step / 45.0, Step / 45.0);
        State.Storm = std::clamp(State.Storm + Delta, 0.0, 1.0);
    }
}

inline double SunFactor(const FState& State)
{
    constexpr double Pi = 3.14159265358979323846;
    return std::max(0.0, std::sin((State.Hours - 6.0) * Pi / 12.0)) * (1.0 - State.Storm * 0.75);
}

inline double WaveHeightCm(const FState& State)
{
    return 22.0 + 78.0 * State.Storm;
}

inline double WindHeadingDegrees(const FState& State)
{
    return 15.0 + 25.0 * State.Storm;
}

inline double WindSpeedFactor(const FState& State)
{
    return 1.0 + 0.4 * State.Storm;
}
} // namespace Tides::Weather
