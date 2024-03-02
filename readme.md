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
	kicker.fireNShots(44, 5*1000); // TODO: Tune timeout to how much we need
	wings.closeBackWings();
	pros::delay(200);

	kicker.returnToHome();

	// Turn and go over to the other side
	chassis.turnToHeading(-45);
	chassis.moveLateral(29);
	chassis.swingToHeading(3, SWING_LEFT); // Turn a bit extra 
	chassis.moveLateral(75);


	// Turn, make a push from the side with wings
	chassis.swingToHeading(45, SWING_LEFT);
	wings.flickFrontWings(250);
	chassis.moveLateral(24);
	chassis.swingToHeading(90, SWING_LEFT);
	chassis.ramAndGoBack(800, 127, 10);
	pros::delay(200);

	// Turn and do another push
	// chassis.turnToHeading(-90);
	// chassis.ramAndGoBack(800, -127, 10);

	// Turn & move towards barrier
	chassis.turnToHeading(183);
	// REVIEW - add flick here?
	chassis.moveLateral(44);

	// Turn and do a goofy ahh curved push
	chassis.turnToHeading(235);
	wings.openBackWings();
	pros::delay(500);
	chassis.driveMotors = -127; 
	pros::delay(300);
	chassis.leftMotors = -127;
	chassis.rightMotors = -80;
	pros::delay(800);
	chassis.driveMotors = 0;
	wings.closeBackWings();

	// Go back and turn and go to the side bruh
	chassis.moveLateral(6);
	chassis.turnToHeading(180);
	chassis.moveLateral(33);
	chassis.turnToHeading(90);
	chassis.moveLateral(36);
	wings.openBackWings();
	pros::delay(500);


	// Turn and do a goofy ahh curved push
	chassis.turnToHeading(135);
	chassis.leftMotors = -80;
	chassis.rightMotors = -127;
	pros::delay(1200);
	chassis.driveMotors = 0;
	wings.closeBackWings();

	// GO fwd, go to side, flick triballs out
	chassis.moveLateral(6);
	chassis.turnToHeading(180);
	chassis.moveLateral(20);
	chassis.turnToHeading(90);
	chassis.moveLateral(16);
	wings.openFrontWings();
	chassis.swingToHeading(-20, subsystems::SWING_RIGHT);

	// Turn to the correct angle, drive fwd, turn and score
	chassis.turnToHeading(45);
	wings.closeFrontWings();
	chassis.moveLateral(27);
	chassis.swingToHeading(-45, SWING_RIGHT);

	chassis.moveLateral(12);
	chassis.swingToHeading(-90, SWING_RIGHT);
	chassis.ramAndGoBack(600, 127, 20);
	chassis.ramAndGoBack(600, 127, 10);

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



