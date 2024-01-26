#include "globals.hpp"
#include "main.h"
#include "subsystems/chassis/chassis.hpp"

void subsystems::Chassis::moveLateral(int targetDistance, double maxPower, double settleTime, double settleRange, double timeout) {

    // chassis.tarePosition()
    drivePID.setStopConditionConstants(
        (settleRange != -1) ? settleRange : drivePID.defaultMinSettleError, 
        (settleTime != -1) ? settleTime : drivePID.defaultMinSettleTime, 
        (timeout != -1) ? timeout : drivePID.defaultTimeout
    );

    double startPosition = getAvgEncoderValue();

    // NOTE - There are 300ticks/rev for motors, 400ticks/wheelRevolution for OUR gear ratio!
    float targetPosition = targetDistance * 46.29961 + startPosition; // dist * 400/2pi*r; which is 400 / (2.75 * 3.14159)
    
    // Stall Detection Timer
    double timeSpentStalled = 0;

    while(!(this->drivePID.isSettled())) {
        float error = targetPosition - this->getAvgEncoderValue();
        float power = this->drivePID.compute(error);

        driveMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;
        pros::delay(10);

        // TODO: Check if this aworks
        if(power > MIN_LATERAL_MOVE_POWER && this->getAvgMotorVelocity() < MIN_STALL_VELOCITY) {
            timeSpentStalled += 10;
        } else {
            timeSpentStalled = 0;
        }

        if(timeSpentStalled > MIN_STALL_TIME) {
            inputSystem.rumbleController("... ...");
            break;
        }
        pros::screen::print(pros::E_TEXT_MEDIUM, 5, "velo: %f", this->getAvgMotorVelocity());

        // TODO: Create a quick transition system

		
    }

    driveMotors.brake();
    this->drivePID.resetSystem();
}

void subsystems::Chassis::ramAndGoBack(double delay, double power, double distBack) {
    double startPos = getAvgEncoderValue();
    driveMotors = power;
    pros::delay(delay);
    double endPos = getAvgEncoderValue();
    if (distBack == -1) {
        // Move back how much was moved fwd, and go the opposite direction of the power
        moveLateral(-1 * utils::sign(power) * fabs(countsToInches(endPos - startPos)));
    } else {
        // If specific dist back was specified
        moveLateral( -1 * utils::sign(power) * distBack);
    }
}