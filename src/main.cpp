#include "main.h"
#include "globals.hpp"
#include "pros/motors.h"
#include "subsystems/chassis/chassis.hpp"


using namespace subsystems;


void disabled() {}

void competition_initialize() {
	// autonManager.displaySelection();
	chassis.resetIMUs();
}

void initialize() {
	chassis.startOdometryTask();
	kicker.resetRotationSensor();
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
