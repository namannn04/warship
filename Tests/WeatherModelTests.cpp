#include "Weather/WeatherModel.h"
#include <cassert>
#include <iostream>

using namespace Tides::Weather;

int main()
{
    FState Weather;
    const double MorningSun = SunFactor(Weather);
    assert(MorningSun > 0.0);
    Weather.TargetStorm = 1.0;
    for (int I = 0; I < 40; ++I) Advance(Weather, 0.25);
    assert(Weather.Storm > 0.0 && Weather.Storm < 1.0);
    assert(WaveHeightCm(Weather) > 22.0);
    assert(SunFactor(Weather) < MorningSun);
    for (int I = 0; I < 200; ++I) Advance(Weather, 0.25);
    assert(Weather.Storm == 1.0);
    Weather.TargetStorm = 0.0;
    for (int I = 0; I < 200; ++I) Advance(Weather, 0.25);
    assert(Weather.Storm == 0.0);
    Weather.Hours = 23.99;
    Advance(Weather, 1.0);
    assert(Weather.Hours >= 0.0 && Weather.Hours < 24.0);
    std::cout << "Weather model tests passed\n";
}
