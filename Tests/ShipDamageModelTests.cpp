#include "Ship/ShipDamageModel.h"
#include <cassert>
#include <iostream>

using namespace Tides::Damage;

int main()
{
    FState Ship;
    ApplyHit(Ship, ESection::Hull, 40.0);
    assert(Ship.Hull == 60.0);
    assert(Ship.BreachSeverity == 24.0);
    for (int I = 0; I < 40; ++I) Tick(Ship, 0.25, false);
    assert(Ship.Water > 0.0);
    const double Flooded = Ship.Water;
    RepairHull(Ship, 30.0);
    assert(Ship.BreachSeverity == 0.0);
    for (int I = 0; I < 40; ++I) Tick(Ship, 0.25, true);
    assert(Ship.Water < Flooded);

    ApplyHit(Ship, ESection::Sails, 50.0);
    ApplyHit(Ship, ESection::Mast, 50.0);
    ApplyHit(Ship, ESection::Rudder, 25.0);
    assert(SailEfficiency(Ship) == 0.25);
    assert(RudderEfficiency(Ship) == 0.75);

    FState Doomed;
    ApplyHit(Doomed, ESection::Hull, 100.0);
    for (int I = 0; I < 400; ++I) Tick(Doomed, 0.25, false);
    assert(Doomed.bSunk);
    assert(Doomed.Water == 100.0);
    RepairHull(Doomed, 100.0);
    assert(Doomed.BreachSeverity == 60.0);
    std::cout << "Ship damage model tests passed\n";
}
