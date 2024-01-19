#include "main.h"
#include "globals.hpp"

void disabled() {}



void competition_initialize() {
	// autonManager.displaySelection();
}

void autonomous() {
	// autonManager.runAuton(autonManager.getSelectedAuton());
}

void initialize() {
	subsystems::kicker.resetRotationSensor();
}

void opcontrol() {
	
	while (true) {
		// Run Drive
		subsystems::chassis.arcade(false, true, false);

		// Run other Systems
		subsystems::intake.runOpcontrol();
		subsystems::kicker.runOpcontrol();
		subsystems::wings.runOpcontrol();
		subsystems::elevation.runOpcontrol();

		pros::delay(10);
	}
}
