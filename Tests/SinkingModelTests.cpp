#include "Ship/SinkingModel.h"
#include <cassert>

int main()
{
    using namespace Tides::Sinking;
    FState Sinking;
    Advance(Sinking, 10.0, false);
    assert(Sinking.DepthCm == 0.0);
    Advance(Sinking, -1.0, true);
    assert(Sinking.Seconds == 0.0);
    for (int Step = 0; Step < 6; ++Step) Advance(Sinking, 5.0, true);
    assert(Sinking.Seconds == 30.0);
    assert(Sinking.DepthCm == 300.0);
    assert(Sinking.ListDegrees == 18.75);
    for (int Step = 0; Step < 20; ++Step) Advance(Sinking, 5.0, true);
    assert(Sinking.Seconds == 60.0);
    assert(Sinking.DepthCm == 1200.0);
    assert(Sinking.ListDegrees == 75.0);
}
