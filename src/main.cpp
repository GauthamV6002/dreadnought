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

/*!SECTION
	chassis.moveLateral(24);
	chassis.swingToHeading(90, subsystems::SWING_LEFT);
	chassis.moveLateral(24);
	chassis.turnToHeading(225);
	chassis.moveLateral(40);
	chassis.turnToHeading(0);
*/

void sixBallFromBack() {

	// Intake 1st triball
	intake.setIntakeIn(127);
	chassis.moveLateral(36, 100);
	pros::delay(500);

	// Push alliance triball towards matchload, turn & descore
	chassis.moveLateral(-36, 60);
	chassis.swingToHeading(-45, subsystems::SWING_LEFT, 100);
	wings.openBackWings();
	pros::delay(200);
	chassis.moveLateral(-12, 127);
	chassis.turnToHeading(-140, 80);
	wings.closeBackWings();
	pros::delay(200);
	chassis.turnToHeading(-60, 127);
	// chassis.swingToHeading(-70, SWING_LEFT);

	// Move fwd, turn, push
	chassis.moveLateral(-14, 70);
	chassis.turnToHeading(-90);
	chassis.ramAndGoBack(500, -127, 12);

	// Turn and push the other one in, turn towards last triball
	chassis.turnToHeading(90);
	intake.setIntakeIn(-127);
	chassis.ramAndGoBack(600, 127, 18);
	chassis.turnToHeading(15);
	intake.setIntakeIn(127);

	// Get the close triball, outtake towards goal
	chassis.moveLateral(50);
	chassis.turnToHeading(150);
	intake.setIntakeIn(-127);
	pros::delay(300);

	// Go fwd, turn towards farthest triball, get it
	chassis.moveLateral(10);
	intake.setIntakeIn(127);
	chassis.turnToHeading(50);
	chassis.moveLateral(18);
	pros::delay(300);
	// chassis.moveLateral(17);

	// Turn and do the BIG push
	chassis.turnToHeading(180);
	wings.openFrontWings();
	pros::delay(200);
	chassis.ramAndGoBack(1000, 127);


}

void sixBallRush() {
	// Start from corner of tile beside matchload bar, turned 31deg

	float absoluteStart = 31; // Ref angle is straight up

	// Move fwd to get triball, turn, push both
	wings.openFrontWings();
	pros::delay(400);
	wings.closeFrontWings();
	intake.setIntakeIn(127);
	chassis.moveLateral(63);
	chassis.turnToHeading(90 + absoluteStart);
	wings.openFrontWings();
	intake.setIntakeIn(0);
	chassis.ramAndGoBack(1000, 80, 12);
	wings.closeFrontWings();

	// Get 3rd triball, put it in
	chassis.turnToHeading(absoluteStart + 135);
	intake.setIntakeIn(127);
	chassis.moveLateral(29);
	chassis.moveLateral(-25);
	
	chassis.turnToHeading(absoluteStart + 90);
	intake.setIntakeIn(0);
	chassis.ramAndGoBack(1000, 80, 10);
	chassis.turnToHeading(absoluteStart);

	// // Go back & turn
	// chassis.moveLateral(-51);
	// chassis.turnToHeading(absoluteStart + -90);

	// // Intake 1st triball
	// intake.setIntakeIn(127);
	// chassis.moveLateral(36);
	// pros::delay(400);

	// // Push alliance triball towards matchload, turn & descore
	// chassis.moveLateral(-36, 60);
	// chassis.swingToHeading(-45, subsystems::SWING_LEFT, 100);
	// wings.openBackWings();
	// pros::delay(200);
	// chassis.moveLateral(-12, 127);
	// chassis.turnToHeading(-140, 80);
	// wings.closeBackWings();
	// pros::delay(200);
	// chassis.turnToHeading(-60, 127);
	// // chassis.swingToHeading(-70, SWING_LEFT);

	// // Move fwd, turn, push
	// chassis.moveLateral(-14, 70);
	// chassis.turnToHeading(-90);
	// chassis.ramAndGoBack(500, -127, 12);

	// // Turn and push the other one in, turn towards last triball
	// chassis.turnToHeading(90);
	// intake.setIntakeIn(-127);
	// chassis.ramAndGoBack(600, 127, 18);

	
}

void disruptOneAWP() {

	// Start - Middle of the lexan piece on intake aligns with the first edge of the tile from the left

	//Hit alliance triball, and descore matchload
	wings.openFrontWings();
	wings.openBackWings();
	pros::delay(200);
	wings.closeFrontWings();
	pros::delay(300);
	chassis.turnToHeading(-90);

	// Turn towards middle triball
	wings.closeBackWings();
	pros::delay(200);
	chassis.turnToHeading(26);

	// Get the middle triball, come back
	intake.setIntakeIn(127);
	chassis.moveLateral(46);
	pros::delay(500);
	chassis.moveLateral(-46);

	// TODO - Maybe change for elims?

	// Turn, touch bar, and outtake
	chassis.turnToHeading(105);
	chassis.moveLateral(10);
	chassis.turnToHeading(90);
	chassis.moveLateral(30);
	intake.setIntakeIn(-127);

}

void calibrate() {
	chassis.moveLateral(24);
	chassis.swingToHeading(90, subsystems::SWING_LEFT);
	chassis.moveLateral(24);
	chassis.turnToHeading(225);
	chassis.moveLateral(40);
	chassis.turnToHeading(0);
}
 
void skills() {
	// Start - upper left corner of tile to start, beside matchload bar, *intake facing opposing goal & || to wall*
	intake.setIntakeIn(100);
	chassis.swingToHeading(-50, subsystems::SWING_LEFT, 80);
	intake.setIntakeIn(0);
	chassis.moveLateral(-24, 80);
	chassis.turnToHeading(-90);
	chassis.ramAndGoBack(600, -127, 8);
	chassis.turnToHeading(18);

	// Fire off all shots
	// pros::delay(1000); // TODO: Remove
	wings.openBackWings();
	kicker.fireNShots(44, 32*1000); // TODO: Tune timeout to how much we need
	wings.closeBackWings();
	pros::delay(200);

	kicker.returnToHome();

	// Turn and go over to the other side
	chassis.turnToHeading(-45);
	chassis.moveLateral(26);
	chassis.swingToHeading(0, SWING_LEFT);
	chassis.moveLateral(75);


	// Turn, make a push from the side with wings
	chassis.swingToHeading(45, SWING_LEFT);
	wings.flickFrontWings(250);
	chassis.moveLateral(24);
	chassis.swingToHeading(90, SWING_LEFT);
	chassis.ramAndGoBack(800, 127, 20);
	pros::delay(200);

	// Turn and do another push
	chassis.turnToHeading(-90);
	chassis.ramAndGoBack(800, -127, 10);

	// Turn & move towards barrier
	chassis.turnToHeading(-185);
	// REVIEW - add flick here?
	chassis.moveLateral(44);

	// Turn and do a goofy ahh curved push
	chassis.turnToHeading(-125);
	wings.openBackWings();
	chassis.driveMotors = -127; 
	pros::delay(300);
	chassis.leftMotors = -127;
	chassis.rightMotors = -80;
	pros::delay(800);
	chassis.driveMotors = 0;
	wings.closeBackWings();

	// Go back and turn and go to the side bruh
	chassis.moveLateral(6);
	chassis.turnToHeading(-180);
	chassis.moveLateral(33);
	chassis.turnToHeading(-270);
	chassis.moveLateral(36);
	wings.openBackWings();

	// Turn and do a goofy ahh curved push
	chassis.turnToHeading(-225);
	chassis.leftMotors = -80;
	chassis.rightMotors = -127;
	pros::delay(1200);
	chassis.driveMotors = 0;
	wings.closeBackWings();

	// GO fwd, go to side, flick triballs out
	chassis.moveLateral(6);
	chassis.turnToHeading(-180);
	chassis.moveLateral(20);
	chassis.turnToHeading(-270);
	chassis.moveLateral(16);
	wings.openFrontWings();
	chassis.swingToHeading(-380, subsystems::SWING_RIGHT);

	// Turn to the correct angle, drive fwd, turn and score
	chassis.turnToHeading(-315);
	chassis.moveLateral(27);
	chassis.swingToHeading(-405, SWING_RIGHT);

	chassis.moveLateral(12);
	chassis.swingToHeading(-450, SWING_RIGHT);
	chassis.ramAndGoBack(800, 127);

	// OPTIONAL - Go in for one more push
	// TODO

	// Go for climb
	chassis.turnToHeading(-405);
	chassis.moveLateral(-28);
	chassis.turnToHeading(-355);
	elevation.raiseElevation();
	chassis.moveLateral(-54);
	elevation.closeElevation();
}

void disruptAWP() {
	intake.setIntakeIn(100);
	wings.openFrontWings();
	wings.openBackWings();
	pros::delay(200);
	wings.closeFrontWings();
	pros::delay(300);
	chassis.turnToHeading(-90);

	wings.closeBackWings();
	pros::delay(200);
	chassis.turnToHeading(26);

	chassis.moveLateral(43);
	chassis.turnToHeading(90);

	wings.openFrontWings();
	pros::delay(200);
	chassis.moveLateral(30);
	wings.closeFrontWings();
	chassis.moveLateral(-2);

	chassis.turnToHeading(-45);
	chassis.moveLateral(-60);
	// wings.openBackWings();
	// pros::delay(300);
	// chassis.rightMotors = -100;
	// chassis.leftMotors = -127;
	// pros::delay(1000);
	// chassis.driveMotors = 0;


}

void skillsStart() {
	// Start - upper left corner of tile to start, beside matchload bar, *intake facing opposing goal & || to wall*
	intake.setIntakeIn(100);
	chassis.resetIMUs();
	pros::delay(1000);
	intake.setIntakeIn(0);
	
	chassis.swingToHeading(-50, subsystems::SWING_LEFT, 80);
	chassis.moveLateral(-24, 80);
	chassis.turnToHeading(-90);
	chassis.ramAndGoBack(600, -127, 8);
	chassis.turnToHeading(18);

	wings.openBackWings();
	kicker.matchLoadRoutineIsActive = true; // TODO: Tune timeout to how much we need

	// Wait till first input
	while(abs(inputSystem.getChassisThrottle()) < 5) {
		kicker.runOpcontrol();
		pros::delay(10);
	}
}

void closeSideDisrupt() {
	chassis.moveLateral(54);
	chassis.turnToHeading(90);
	wings.openFrontWings();
	chassis.moveLateral(35);
	wings.closeFrontWings();   
}

void closeSideAWPSafe() {

	wings.openBackWings();
	pros::delay(400);

	intake.setIntakeIn(60);
	pros::delay(400);

	chassis.swingToHeading(-50, subsystems::SWING_RIGHT);
	chassis.swingToHeading(0, subsystems::SWING_RIGHT);
	wings.closeBackWings();
	pros::delay(800);

	// chassis.swingToHeading(-45, subsystems::SWING_RIGHT);
	chassis.moveLateral(10);
	chassis.turnToHeading(-45);
	chassis.moveLateral(30);

	intake.setIntakeIn(-127);
}
 
void autonomous() {
	// autonManager.runAuton(autonManager.getSelectedAuton());
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	sixBallFromBack();
	// closeSideAWPSafe();
	// skills();
	// closeSideDisrupt();
	// disruptAWP();
	// sixBallRush();
	// disruptOneAWP();
}

void opcontrol() {
	
	// chassis.setBrakeMode(pros::E_MOTOR_BRAKE_HOLD);
	// skillsStart();
	chassis.setBrakeMode(pros::E_MOTOR_BRAKE_COAST);

	while (true) {
		// Run Drive
		// Check if sai prefers joystick curves for driver
		subsystems::chassis.arcade(false, true, false);

		// Run other Systems
		subsystems::intake.runOpcontrol();
		subsystems::kicker.runOpcontrol();
		subsystems::wings.runOpcontrol();
		subsystems::elevation.runOpcontrol();

		pros::screen::print(TEXT_MEDIUM, 5, "imu: %f", chassis.getAvgEncoderValue()); 
		pros::screen::print(TEXT_MEDIUM, 6, "imu: %f", chassis.getAvgHeading()); 

		pros::delay(10);
	}
}
