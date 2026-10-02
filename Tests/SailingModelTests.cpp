#include "Ship/SailingModel.h"
#include <cassert>
#include <cmath>
#include <iostream>

using namespace Tides::Sailing;

int main()
{
    const FConfig Config;
    FState State;
    FCommand Command;
    Advance(State, Config, Command, 0.05);
    assert(State.Speed > 0.0 && State.Speed <= Config.Acceleration * 0.05 + 0.0001);
    assert(State.X > 0.0);
    assert(std::abs(State.YawDegrees) < 0.0001);

    const double BeforeTurn = State.YawDegrees;
    Command.Rudder = 1.0;
    for (int I = 0; I < 100; ++I) Advance(State, Config, Command, 0.05);
    assert(State.YawDegrees > BeforeTurn);
    assert(State.YawDegrees < 40.0); // A large vessel cannot spin quickly.

    Command.bAnchored = true;
    const double BeforeAnchor = State.Speed;
    for (int I = 0; I < 100; ++I) Advance(State, Config, Command, 0.05);
    assert(State.Speed < BeforeAnchor);
    assert(State.Speed >= 0.0);

    FState A;
    FState B;
    for (int I = 0; I < 4; ++I) Advance(A, Config, FCommand{}, 0.05);
    Advance(B, Config, FCommand{}, 0.2);
    assert(std::abs(A.Speed - B.Speed) < 0.0001);
    assert(std::abs(A.X - B.X) < 0.0001);

    FState WithWind;
    FState AgainstWind;
    AgainstWind.YawDegrees = 180.0;
    for (int I = 0; I < 80; ++I)
    {
        Advance(WithWind, Config, FCommand{}, 0.05);
        Advance(AgainstWind, Config, FCommand{}, 0.05);
    }
    assert(WithWind.Speed > AgainstWind.Speed);

    assert(RudderForHeading(350.0, 10.0) > 0.0);
    assert(RudderForHeading(10.0, 350.0) < 0.0);
    assert(std::abs(RudderForHeading(125.0, 125.0)) < 0.0001);

    std::cout << "Sailing model tests passed\n";
}
