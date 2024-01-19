#include "main.h"

void subsystems::Chassis::moveLateral(int targetDistance, double maxPower = 127, double settleTime = -1, double settleRange = -1, double timeout = -1) {

    // Reset positions for simpler error calculation
    chassis.tarePosition();
    drivePID.setStopConditionConstants(
        (settleRange != -1) ? settleRange : drivePID.defaultMinSettleError, 
        (settleTime != -1) ? settleTime : drivePID.defaultMinSettleTime, 
        (timeout != -1) ? timeout : drivePID.defaultTimeout
    );

    float targetPosition = targetDistance * 46.29961; // dist * 300/2pi*r; which is 300 / (2.75 * 3.14159)
    //NOTE - Blue motors have 300ticks/rev

    double timeSpentStalled = 0;

    const double MIN_STALL_POWER = 30, MIN_STALL_VELOCITY = 4, MIN_STALL_TIME = 400;


    while(!(this->drivePID.isSettled())) {
        float error = targetPosition - this->getAvgEncoderValue();
        float power = this->drivePID.compute(error);

        driveMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;
        pros::delay(10);

        // TODO: Fix Stall Detection
        // if(power > MIN_STALL_POWER && this->getAvgMotorVelocity() < MIN_STALL_VELOCITY) {
        //     timeSpentStalled += 10;
        // } else {
        //     timeSpentStalled = 0;
        // }

        // if(timeSpentStalled > MIN_STALL_TIME) break;
		
    }

    driveMotors.brake();
    this->drivePID.resetSystem();
}