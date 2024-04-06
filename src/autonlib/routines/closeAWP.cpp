#include "globals.hpp"
#include "main.h"

using namespace subsystems;
using autonlib::HEADINGS;

void closeSideAWPSafe() {
    wings.openFrontWingsFor(300);
    chassis.turnToHeading(HEADINGS::RIGHT);
}

void initCloseAWPRoutines() {
    autonlib::Routine closeSideAWPSafeRoutine("Close AWP Safe", 24, 16, 180, closeSideAWPSafe);
    autonManager.addRoutine(closeSideAWPSafeRoutine);
}
