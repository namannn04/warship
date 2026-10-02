#include "Ship/ShipFireModel.h"
#include <cassert>

int main()
{
    using namespace Tides::Fire;
    FState Fire;
    Ignite(Fire, EZone::Deck, 60.0);
    Ignite(Fire, EZone::Deck, -10.0);
    assert(HeatAt(Fire, EZone::Deck) == 60.0);
    Advance(Fire, 0.25, 0.0, 0.0);
    assert(HeatAt(Fire, EZone::Sails) > 0.0);
    assert(HeatAt(Fire, EZone::Hold) > 0.0);
    assert(StructuralDamagePerSecond(Fire, EZone::Deck) > 0.0);

    FState Dry;
    FState Wet;
    Ignite(Dry, EZone::Deck, 80.0);
    Ignite(Wet, EZone::Deck, 80.0);
    for (int Step = 0; Step < 80; ++Step)
    {
        Advance(Dry, 0.25, 1.0, 0.0);
        Advance(Wet, 0.25, 1.0, 1.0);
    }
    assert(HeatAt(Dry, EZone::Sails) > HeatAt(Wet, EZone::Sails));
    assert(HeatAt(Dry, EZone::Deck) > HeatAt(Wet, EZone::Deck));

    Extinguish(Dry, EZone::Deck, 500.0);
    assert(HeatAt(Dry, EZone::Deck) == 0.0);
    Ignite(Dry, EZone::Hold, 150.0);
    assert(HeatAt(Dry, EZone::Hold) == 100.0);
    assert(StructuralDamagePerSecond(FState{}, EZone::Hold) == 0.0);
}
