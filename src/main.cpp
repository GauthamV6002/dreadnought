#include "main.h"
#include "display/lv_core/lv_obj.h"
#include "displaylib/display.hpp"
#include "globals.hpp"
#include "pros/motors.h"
#include "subsystems/chassis/chassis.hpp"


using namespace subsystems;

void disabled() {}

void competition_initialize() {
	
	// Smart Start system must be started lined up w/ the wall; is blocking
	// autonManager.smartStartInit(); 

	// Display Auton Selector, handles itself
	// autonManager.displaySelector();
}

void initialize() {
	// autonManager.smartStartInit();
	autonManager.displaySelector();
}
 
void autonomous() {
	// autonManager.runAuton(autonManager.getSelectedAuton());
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_BRAKE);
	

}

void opcontrol() {

	while (true) {
		// Run Drive
		subsystems::chassis.arcade(true, true, false);

		// Run Subsystems
		subsystems::intake.runOpcontrol();
		subsystems::kicker.runOpcontrol();
		subsystems::wings.runOpcontrol();
		subsystems::elevation.runOpcontrol();

		// Run Controller Feedback System
		subsystems::inputSystem.runControllerFeedback();

		pros::delay(10);
	}
}
