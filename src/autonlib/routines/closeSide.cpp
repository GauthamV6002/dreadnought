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


void autonlib::AutonManager::initCloseSideRoutines() {
    // TODO: Change Start Positions/Headings
    autonlib::Routine disruptCentralTriballRoutine("A. Mid-Rush", 0, 0, 0, disruptCentralTriball, CLOSE_SIDE);
    autonManager.addRoutine(disruptCentralTriballRoutine);

    autonlib::Routine disruptBarrierTriballRoutine("B. Barrier Rush", 0, 0, 0, disruptBarrierTriball, CLOSE_SIDE);
    autonManager.addRoutine(disruptBarrierTriballRoutine);

    autonlib::Routine disruptBothTriballsWithWingsRoutine("C. Wings-Rush", 0, 0, 0, disruptBothTriballsWithWings, CLOSE_SIDE);
    autonManager.addRoutine(disruptBothTriballsWithWingsRoutine);

    autonlib::Routine disruptCentralThenBarrierRoutine("D. Intake-Wing Rush", 0, 0, 0, disruptCentralThenBarrier, CLOSE_SIDE);
    autonManager.addRoutine(disruptCentralThenBarrierRoutine);

    autonlib::Routine disruptAWPRoutine("E. Mid-Rush AWP", 0, 0, 0, disruptAWP, CLOSE_SIDE);
    autonManager.addRoutine(disruptAWPRoutine);

    autonlib::Routine closeSideSafeRoutine("F. Safe AWP", 0, 0, 0, closeSideSafe, CLOSE_SIDE);
    autonManager.addRoutine(closeSideSafeRoutine);
}
