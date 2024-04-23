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
	// Open wings for alliance ball
	wings.openFrontWingsFor(150);
	wings.closeFrontWings();

	// Get middle triballs and score both
	intake.setIntakeIn(127);
	chassis.moveLateral(63);
	pros::delay(200);
	chassis.turnToHeading(93);
	wings.openFrontWings();
	chassis.driveMotors = 127;
	pros::delay(200);
	intake.setIntakeIn(-127);
	pros::delay(500);
	wings.closeFrontWings();
	chassis.moveLateral(-16);

	// Get next triball, score it
	chassis.turnToHeading(217);
	intake.setIntakeIn(127);
	chassis.moveLateral(23);
	chassis.moveLateral(-4);
	chassis.swingToHeading(88, subsystems::SWING_LEFT);

	// Score the triball	
	wings.openFrontWings();
	chassis.driveMotors = 127;
	pros::delay(100);
	intake.setIntakeIn(-127);
	pros::delay(750);
	wings.closeFrontWings();
	chassis.moveLateral(-4);

	// Turn, go back & get the triball in the alley
	chassis.turnToHeading(0);
	chassis.moveLateral(-48);
	chassis.turnToHeading(-90);
	intake.setIntakeIn(127);
	chassis.moveLateral(24);
	pros::delay(600);

	// Push all triballs on the side in
	chassis.moveLateral(-30);
	chassis.turnToHeading(60);
	wings.openFrontWings();

	// Descore & score triballs
	chassis.moveLateral(8);
	chassis.turnToHeading(-10);
	chassis.turnToHeading(20);
	intake.setIntakeIn(-127);
	chassis.driveMotors = 127;
	pros::delay(300);
	wings.closeFrontWings();
	pros::delay(400);

	chassis.moveLateral(-12);

	chassis.turnToHeading(10);
	chassis.driveMotors = 127;
	pros::delay(600);
	chassis.moveLateral(-12);
}

void chinaRush() {
    
}

void safe6BallAWP() {
    
}


void autonlib::AutonManager::initFarSideRoutines() {
    // TODO: Change Start Positions/Headings
    autonlib::Routine farMidRushRoutine("G. Mid-Rush", 0, 0, 0, rushForCentralTriball, FAR_SIDE);
    autonManager.addRoutine(farMidRushRoutine);

    autonlib::Routine farBarrierRushRoutine("H. Barrier Rush", 0, 0, 0, rushForBarrierTriball, FAR_SIDE);
    autonManager.addRoutine(farBarrierRushRoutine);

    autonlib::Routine farBothRushRoutine("I. Both-Rush", 0, 0, 33, rushForMidTriballs, FAR_SIDE);
    autonManager.addRoutine(farBothRushRoutine);
    
    autonlib::Routine chinaRushRoutine("J. China-Rush", 0, 0, 0, chinaRush, FAR_SIDE);
    autonManager.addRoutine(chinaRushRoutine);

	autonlib::Routine safe6BallRoutine("K. Safe 6-Ball", 0, 0, -90, safe6BallAWP, FAR_SIDE);
    autonManager.addRoutine(safe6BallRoutine);
}