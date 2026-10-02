#include "Ship/ShipInventoryModel.h"
#include <cassert>
#include <iostream>

using namespace Tides::Inventory;

int main()
{
    FState Supplies;
    assert(ConsumePowder(Supplies) && Supplies.PowderCharges == 59);
    assert(ConsumeCannonball(Supplies) && Supplies.Cannonballs == 59);
    assert(ConsumePlanks(Supplies, 4) && Supplies.Planks == 26);
    assert(!ConsumePlanks(Supplies, 27) && Supplies.Planks == 26);
    AddCargo(Supplies, 20);
    assert(Supplies.CargoCrates == 20);
    assert(CargoSpeedFactor(Supplies) < 1.0);
    AddCargo(Supplies, -100);
    assert(Supplies.CargoCrates == 0);
    Supplies.PowderCharges = 0;
    assert(!ConsumePowder(Supplies));
    std::cout << "Ship inventory model tests passed\n";
}
