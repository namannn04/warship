#pragma once

// Localized ship condition independent of Unreal. Values are 0..100 unless noted.
#include <algorithm>

namespace Tides::Damage
{
enum class ESection { Hull, Sails, Mast, Rudder, Cannon };

struct FState
{
    double Hull = 100.0;
    double Sails = 100.0;
    double Mast = 100.0;
    double Rudder = 100.0;
    double Cannons = 100.0;
    double BreachSeverity = 0.0;
    double Water = 0.0;
    double Fire = 0.0;
    bool bSunk = false;
};

inline double& SectionValue(FState& State, ESection Section)
{
    switch (Section)
    {
    case ESection::Hull: return State.Hull;
    case ESection::Sails: return State.Sails;
    case ESection::Mast: return State.Mast;
    case ESection::Rudder: return State.Rudder;
    case ESection::Cannon: return State.Cannons;
    }
    return State.Hull;
}

inline void ApplyHit(FState& State, ESection Section, double Strength)
{
    if (State.bSunk) return;
    const double Damage = std::clamp(Strength, 0.0, 100.0);
    double& Integrity = SectionValue(State, Section);
    Integrity = std::max(0.0, Integrity - Damage);
    if (Section == ESection::Hull) State.BreachSeverity = std::min(100.0, State.BreachSeverity + Damage * 0.6);
}

inline void Tick(FState& State, double DeltaSeconds, bool bPumping)
{
    if (State.bSunk || DeltaSeconds <= 0.0) return;
    const double Step = std::min(DeltaSeconds, 0.25);
    const double Inflow = State.BreachSeverity * 0.025 * Step;
    const double Pumping = bPumping ? 1.25 * Step : 0.0;
    State.Water = std::clamp(State.Water + Inflow - Pumping, 0.0, 100.0);
    State.bSunk = State.Water >= 100.0;
}

inline void RepairHull(FState& State, double Work)
{
    if (State.bSunk) return;
    const double Effort = std::max(0.0, Work);
    State.BreachSeverity = std::max(0.0, State.BreachSeverity - Effort);
    State.Hull = std::min(100.0, State.Hull + Effort * 0.5);
}

inline double SailEfficiency(const FState& State)
{
    return std::clamp((State.Sails / 100.0) * (State.Mast / 100.0), 0.0, 1.0);
}

inline double RudderEfficiency(const FState& State)
{
    return std::clamp(State.Rudder / 100.0, 0.0, 1.0);
}
} // namespace Tides::Damage
