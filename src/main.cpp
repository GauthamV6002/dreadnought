#include "main.h"
#include "globals.hpp"
#include "pros/motors.h"
#include "subsystems/chassis/chassis.hpp"

using namespace subsystems;

void disabled() {}



void competition_initialize() {
	// autonManager.displaySelection();
}

void initialize() {
	kicker.resetRotationSensor();
	chassis.resetIMUs();
}

void autonomous() {
	// autonManager.runAuton(autonManager.getSelectedAuton());
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);

	chassis.moveLateral(24);
	chassis.swingToHeading(90, subsystems::SWING_LEFT);
	chassis.moveLateral(24);
	chassis.turnToHeading(225);
	chassis.moveLateral(40);
	chassis.turnToHeading(0);

}

void opcontrol() {
	
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// Run Drive
		subsystems::chassis.arcade(false, true, false);

		// Run other Systems
		subsystems::intake.runOpcontrol();
		subsystems::kicker.runOpcontrol();
		subsystems::wings.runOpcontrol();
		subsystems::elevation.runOpcontrol();

		pros::screen::print(TEXT_MEDIUM, 5, "imu: %f", chassis.getAvgHeading()); 

		pros::delay(10);
	}
}
