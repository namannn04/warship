#pragma once

// Ship-wide supplies: one source of truth for guns, repairs and provisions.
#include <algorithm>

namespace Tides::Inventory
{
struct FState
{
    int Planks = 30;
    int PowderCharges = 60;
    int Cannonballs = 60;
    int FoodRations = 120;
    int CargoCrates = 0;
};

inline bool ConsumePlanks(FState& State, int Count)
{
    if (Count <= 0 || State.Planks < Count) return false;
    State.Planks -= Count;
    return true;
}

inline bool ConsumePowder(FState& State)
{
    if (State.PowderCharges <= 0) return false;
    --State.PowderCharges;
    return true;
}

inline bool ConsumeCannonball(FState& State)
{
    if (State.Cannonballs <= 0) return false;
    --State.Cannonballs;
    return true;
}

inline void AddCargo(FState& State, int Crates)
{
    State.CargoCrates = std::max(0, State.CargoCrates + Crates);
}

inline double CargoSpeedFactor(const FState& State)
{
    return std::clamp(1.0 - State.CargoCrates * 0.003, 0.7, 1.0);
}
} // namespace Tides::Inventory
