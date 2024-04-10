#include "autonlib/autonlib.hpp"
#include "globals.hpp"
#include "main.h"

using namespace subsystems;
using autonlib::HEADINGS;

void disruptCentralTriball() {
    
}

void disruptBarrierTriball() {
    
}

void disruptBothTriballsWithWings() {
    
}

void disruptCentralThenBarrier() {
    
}

// Main AWP Auton
void disruptAWP() {

}

// ONLY does AWP tasks
void closeSideSafe() {

}


void autonlib::AutonManager::initFarSideRoutines() {
    // TODO: Change Start Positions/Headings
    autonlib::Routine disruptCentralTriballRoutine("Far Mid-Rush", 0, 0, 0, disruptCentralTriball);
    autonManager.addRoutine(disruptCentralTriballRoutine);

    autonlib::Routine disruptBarrierTriballRoutine("Far Barrier Rush", 0, 0, 0, disruptBarrierTriball);
    autonManager.addRoutine(disruptBarrierTriballRoutine);

    autonlib::Routine disruptBothTriballsWithWingsRoutine("Far Both-Rush", 0, 0, 0, disruptBothTriballsWithWings);
    autonManager.addRoutine(disruptBothTriballsWithWingsRoutine);

    autonlib::Routine disruptCentralThenBarrierRoutine("Far Barrier Rush", 0, 0, 0, disruptCentralThenBarrier);
    autonManager.addRoutine(disruptCentralThenBarrierRoutine);

    autonlib::Routine disruptAWPRoutine("Far Both-Rush", 0, 0, 0, disruptAWP);
    autonManager.addRoutine(disruptAWPRoutine);

    autonlib::Routine closeSideSafeRoutine("Far Both-Rush", 0, 0, 0, closeSideSafe);
    autonManager.addRoutine(closeSideSafeRoutine);
}
