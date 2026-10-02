#pragma once

#include <algorithm>
#include <cmath>

namespace Tides::NavalAI
{
enum class EMode { Chase, Broadside, Disengage };
enum class ESide { Port, Starboard };

struct FDecision
{
    EMode Mode = EMode::Chase;
    ESide FiringSide = ESide::Port;
    double DesiredHeadingDegrees = 0.0;
    double SailPower = 0.5;
    bool bMayFire = false;
};

inline double WrapDegrees(double Degrees)
{
    return std::remainder(Degrees, 360.0);
}

inline FDecision Decide(double OwnX, double OwnY, double OwnHeadingDegrees,
    double TargetX, double TargetY, double OwnHullPercent)
{
    constexpr double Pi = 3.14159265358979323846;
    const double DeltaX = TargetX - OwnX;
    const double DeltaY = TargetY - OwnY;
    const double Distance = std::hypot(DeltaX, DeltaY);
    const double TargetBearing = std::atan2(DeltaY, DeltaX) * 180.0 / Pi;
    const double RelativeBearing = WrapDegrees(TargetBearing - OwnHeadingDegrees);
    FDecision Decision;
    Decision.FiringSide = RelativeBearing < 0.0 ? ESide::Port : ESide::Starboard;

    if (OwnHullPercent < 25.0)
    {
        Decision.Mode = EMode::Disengage;
        Decision.DesiredHeadingDegrees = WrapDegrees(TargetBearing + 180.0);
        Decision.SailPower = 1.0;
    }
    else if (Distance > 4300.0)
    {
        Decision.Mode = EMode::Chase;
        Decision.DesiredHeadingDegrees = TargetBearing;
        Decision.SailPower = 0.8;
    }
    else
    {
        Decision.Mode = EMode::Broadside;
        Decision.DesiredHeadingDegrees = WrapDegrees(TargetBearing +
            (Decision.FiringSide == ESide::Port ? 90.0 : -90.0));
        Decision.SailPower = Distance < 1700.0 ? 0.2 : 0.45;
        Decision.bMayFire = Distance >= 500.0 && Distance <= 4300.0
            && std::abs(std::abs(RelativeBearing) - 90.0) <= 25.0;
    }
    Decision.DesiredHeadingDegrees = WrapDegrees(Decision.DesiredHeadingDegrees);
    return Decision;
}
} // namespace Tides::NavalAI
