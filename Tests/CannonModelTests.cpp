#include "Ship/CannonModel.h"
#include <cassert>
#include <iostream>
#include <string>

using namespace Tides::Cannon;

int main()
{
    FState Cannon;
    assert(!Fire(Cannon));
    assert(Cannon.ShotsFired == 0);
    assert(std::string(StageLabel(Cannon.Stage)) == "Clean barrel");
    assert(AdvanceLoading(Cannon) && Cannon.Stage == EStage::Clean);
    assert(AdvanceLoading(Cannon) && Cannon.Stage == EStage::Powder);
    assert(AdvanceLoading(Cannon) && Cannon.Stage == EStage::Ball);
    assert(AdvanceLoading(Cannon) && Cannon.Stage == EStage::Rammed);
    assert(AdvanceLoading(Cannon) && Cannon.Stage == EStage::Ready);
    assert(!AdvanceLoading(Cannon));
    assert(Fire(Cannon) && Cannon.ShotsFired == 1);
    assert(!Fire(Cannon));
    Tick(Cannon, 0.4);
    assert(Cannon.Stage == EStage::Recoil);
    Tick(Cannon, 0.5);
    assert(Cannon.Stage == EStage::Fouled);
    assert(AdvanceLoading(Cannon));
    std::cout << "Cannon model tests passed\n";
}
