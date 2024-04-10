#include "autonlib/autonlib.hpp"
#include "globals.hpp"
#include "main.h"

using namespace subsystems;
using autonlib::HEADINGS;

void rushForCentralTriball() {
    
}

void rushForBarrierTriball() {
    
}

void rushForMidTriballs() {
    
}


void autonlib::AutonManager::initFarSideRoutines() {
    // TODO: Change Start Positions/Headings
    autonlib::Routine farMidRushRoutine("Far Mid-Rush", 0, 0, 0, rushForCentralTriball);
    autonManager.addRoutine(farMidRushRoutine);

    autonlib::Routine farBarrierRushRoutine("Far Barrier Rush", 0, 0, 0, rushForBarrierTriball);
    autonManager.addRoutine(farBarrierRushRoutine);

    autonlib::Routine farBothRushRoutine("Far Both-Rush", 0, 0, 0, rushForMidTriballs);
    autonManager.addRoutine(farBothRushRoutine);
}
