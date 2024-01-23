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

	

	// chassis.moveLateral(-24);
	// chassis.moveLateral(24);

	// chassis.driveMotors = -127;

	// while(true) {
	// 	pros::screen::print(TEXT_MEDIUM, 1, "velocity: %f", chassis.backLeft.get_actual_velocity()); 
	// 	pros::screen::print(TEXT_MEDIUM, 2, "current: %f", chassis.backLeft.get_current_draw()); 
	// 	pros::screen::print(TEXT_MEDIUM, 3, "over: %f", chassis.backLeft.is_over_current()); 
	// 	pros::delay(20);
	// }
	
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
