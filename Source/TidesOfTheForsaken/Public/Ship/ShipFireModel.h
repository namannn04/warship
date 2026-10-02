#pragma once

#include <algorithm>
#include <array>
#include <cstddef>

namespace Tides::Fire
{
enum class EZone : std::size_t { Deck, Sails, Hold, Count };

struct FState
{
    std::array<double, static_cast<std::size_t>(EZone::Count)> Heat{};
};

constexpr std::size_t Index(EZone Zone) { return static_cast<std::size_t>(Zone); }

inline double HeatAt(const FState& State, EZone Zone) { return State.Heat[Index(Zone)]; }

inline void Ignite(FState& State, EZone Zone, double Strength)
{
    State.Heat[Index(Zone)] = std::clamp(State.Heat[Index(Zone)] + std::max(0.0, Strength), 0.0, 100.0);
}

inline void Extinguish(FState& State, EZone Zone, double Work)
{
    State.Heat[Index(Zone)] = std::max(0.0, State.Heat[Index(Zone)] - std::max(0.0, Work));
}

// Wind and rain are normalized 0..1. Spread uses a snapshot so one step cannot
// chain through multiple zones. The caller supplies small fixed or frame steps.
inline void Advance(FState& State, double Seconds, double Wind, double Rain)
{
    if (Seconds <= 0.0) return;
    const double Step = std::min(Seconds, 0.25);
    const double WindFactor = 1.0 + std::clamp(Wind, 0.0, 1.0);
    const double RainFactor = std::clamp(Rain, 0.0, 1.0);
    const auto Previous = State.Heat;
    constexpr std::size_t Deck = Index(EZone::Deck);
    constexpr std::size_t Sails = Index(EZone::Sails);
    constexpr std::size_t Hold = Index(EZone::Hold);
    const double Spread = (1.0 - RainFactor * 0.8) * WindFactor * Step;
    const double Gains[3] = {
        (Previous[Sails] * 0.012 + Previous[Hold] * 0.006) * Spread,
        Previous[Deck] * 0.018 * Spread,
        Previous[Deck] * 0.008 * Spread
    };
    for (std::size_t Zone = 0; Zone < State.Heat.size(); ++Zone)
    {
        const double Cooling = (0.12 + RainFactor * (Zone == Hold ? 0.4 : 2.0)) * Step;
        State.Heat[Zone] = std::clamp(Previous[Zone] + Gains[Zone] - Cooling, 0.0, 100.0);
    }
}

inline double StructuralDamagePerSecond(const FState& State, EZone Zone)
{
    return HeatAt(State, Zone) > 15.0 ? HeatAt(State, Zone) * 0.012 : 0.0;
}
} // namespace Tides::Fire
