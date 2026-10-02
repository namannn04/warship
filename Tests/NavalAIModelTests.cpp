#include "Combat/NavalAIModel.h"
#include <cassert>
#include <cmath>

int main()
{
    using namespace Tides::NavalAI;
    const FDecision Chase = Decide(0.0, 0.0, 0.0, 6000.0, 0.0, 100.0);
    assert(Chase.Mode == EMode::Chase);
    assert(Chase.DesiredHeadingDegrees == 0.0);
    assert(!Chase.bMayFire);

    const FDecision Port = Decide(0.0, 0.0, 0.0, 0.0, -3000.0, 100.0);
    assert(Port.Mode == EMode::Broadside);
    assert(Port.FiringSide == ESide::Port);
    assert(Port.bMayFire);
    assert(std::abs(Port.DesiredHeadingDegrees) < 0.001);

    const FDecision Starboard = Decide(0.0, 0.0, 0.0, 0.0, 3000.0, 100.0);
    assert(Starboard.FiringSide == ESide::Starboard);
    assert(Starboard.bMayFire);
    assert(std::abs(Starboard.DesiredHeadingDegrees) < 0.001);

    const FDecision WrongAngle = Decide(0.0, 0.0, 0.0, 3000.0, 0.0, 100.0);
    assert(!WrongAngle.bMayFire);
    const FDecision Close = Decide(0.0, 0.0, 0.0, 0.0, -300.0, 100.0);
    assert(!Close.bMayFire);
    const FDecision Retreat = Decide(0.0, 0.0, 0.0, 3000.0, 0.0, 20.0);
    assert(Retreat.Mode == EMode::Disengage);
    assert(!Retreat.bMayFire);
    assert(std::abs(std::abs(Retreat.DesiredHeadingDegrees) - 180.0) < 0.001);
}
