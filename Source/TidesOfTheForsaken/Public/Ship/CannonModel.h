#pragma once

// The cannon cycle is independent of Unreal so crew AI and player input can
// drive the same state machine, with its transitions tested in isolation.
#include <algorithm>

namespace Tides::Cannon
{
enum class EStage
{
    Fouled,
    Clean,
    Powder,
    Ball,
    Rammed,
    Ready,
    Recoil
};

struct FState
{
    EStage Stage = EStage::Fouled;
    double RecoilRemainingSeconds = 0.0;
    int ShotsFired = 0;
};

inline bool AdvanceLoading(FState& State)
{
    switch (State.Stage)
    {
    case EStage::Fouled: State.Stage = EStage::Clean; return true;
    case EStage::Clean: State.Stage = EStage::Powder; return true;
    case EStage::Powder: State.Stage = EStage::Ball; return true;
    case EStage::Ball: State.Stage = EStage::Rammed; return true;
    case EStage::Rammed: State.Stage = EStage::Ready; return true;
    default: return false;
    }
}

inline bool Fire(FState& State)
{
    if (State.Stage != EStage::Ready) return false;
    State.Stage = EStage::Recoil;
    State.RecoilRemainingSeconds = 0.8;
    ++State.ShotsFired;
    return true;
}

inline void Tick(FState& State, double DeltaSeconds)
{
    if (State.Stage != EStage::Recoil) return;
    State.RecoilRemainingSeconds = std::max(0.0, State.RecoilRemainingSeconds - std::max(0.0, DeltaSeconds));
    if (State.RecoilRemainingSeconds <= 0.0) State.Stage = EStage::Fouled;
}

inline const char* StageLabel(EStage Stage)
{
    switch (Stage)
    {
    case EStage::Fouled: return "Clean barrel";
    case EStage::Clean: return "Insert powder";
    case EStage::Powder: return "Insert cannonball";
    case EStage::Ball: return "Ram shot";
    case EStage::Rammed: return "Run out cannon";
    case EStage::Ready: return "Ready to fire";
    case EStage::Recoil: return "Recoiling";
    }
    return "Unknown";
}
} // namespace Tides::Cannon
