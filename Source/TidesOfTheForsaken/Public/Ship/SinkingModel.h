#pragma once

#include <algorithm>

namespace Tides::Sinking
{
struct FState
{
    double Seconds = 0.0;
    double DepthCm = 0.0;
    double ListDegrees = 0.0;
    double PitchDegrees = 0.0;
};

inline void Advance(FState& State, double DeltaSeconds, bool bSunk)
{
    if (!bSunk || DeltaSeconds <= 0.0) return;
    State.Seconds = std::min(60.0, State.Seconds + std::min(DeltaSeconds, 5.0));
    const double Fraction = State.Seconds / 60.0;
    State.DepthCm = 1200.0 * Fraction * Fraction;
    State.ListDegrees = 75.0 * Fraction * Fraction;
    State.PitchDegrees = 18.0 * Fraction;
}
} // namespace Tides::Sinking
