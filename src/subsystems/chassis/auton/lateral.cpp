#include "globals.hpp"
#include "main.h"
#include "subsystems/chassis/chassis.hpp"

void subsystems::Chassis::moveLateral(int targetDistance, double maxPower, float chainNextGain, double settleTime, double settleRange, double timeout) {

    // chassis.tarePosition()
    drivePID.setStopConditionConstants(
        (settleRange != -1) ? settleRange : drivePID.defaultMinSettleError, 
        (settleTime != -1) ? settleTime : drivePID.defaultMinSettleTime, 
        (timeout != -1) ? timeout : drivePID.defaultTimeout
    );

    double startPosition = getAvgEncoderValue();

    // NOTE - There are 300ticks/rev for motors, 400ticks/wheelRevolution for OUR gear ratio!
    float targetPosition = targetDistance * 46.29961 + startPosition; // dist * 400/2pi*r; which is 400 / (2.75 * 3.14159)
    
    while(!(this->drivePID.isSettled())) {
        float error = targetPosition - this->getAvgEncoderValue();
        float power = this->drivePID.compute(error);

        // Motion Chaining
        // if(chainNextGain != -1) power *= chainNextGain;
        // if(setPoint)

        driveMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;
        pros::delay(10);

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