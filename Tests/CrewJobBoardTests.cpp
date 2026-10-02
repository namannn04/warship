#include "Crew/CrewJobBoard.h"
#include <cassert>
#include <iostream>

using namespace Tides::Crew;

int main()
{
    FJobBoard Board;
    const auto Gunner = static_cast<std::uint8_t>(ERole::Gunner);
    const auto Carpenter = static_cast<std::uint8_t>(ERole::Carpenter);
    const int Reload = Board.Post(EJobKind::ReloadCannon, 7, 2, Gunner, 10.0, 0.0);
    const int Emergency = Board.Post(EJobKind::PatchHull, 3, 10, Carpenter, 100.0, 0.0);
    assert(Board.Post(EJobKind::PatchHull, 3, 11, Carpenter, 100.0, 0.0) == Emergency);
    assert(Board.Count() == 2);
    assert(Board.ClaimBest(1, ERole::Gunner, 0.0, 0.0) == Reload);
    assert(Board.ClaimBest(2, ERole::Gunner, 0.0, 0.0) == -1);
    assert(Board.ClaimBest(3, ERole::Carpenter, 0.0, 0.0) == Emergency);
    const int Fire = Board.Post(EJobKind::ExtinguishFire, 0, 120, Carpenter, 300.0, 0.0);
    Board.ReleaseCrew(3);
    assert(Board.ClaimBest(3, ERole::Carpenter, 0.0, 0.0) == Fire);
    assert(Board.Complete(Fire, 3));
    assert(!Board.Complete(Emergency, 1));
    assert(Board.ClaimBest(4, ERole::Carpenter, 0.0, 0.0) == Emergency);
    assert(Board.Complete(Emergency, 4));
    assert(Board.Cancel(EJobKind::ReloadCannon, 7));
    assert(Board.Count() == 0);
    std::cout << "Crew job board tests passed\n";
}
