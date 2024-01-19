#include "main.h"

namespace subsystems {
    
    void Chassis::turnToHeading(double targetHeading, double maxPower, double settleTime = -1, double settleRange = -1, double timeout = -1) {

        turnPID.setStopConditionConstants(
            (settleRange != -1) ? settleRange : turnPID.defaultMinSettleError, 
            (settleTime != -1) ? settleTime : turnPID.defaultMinSettleTime, 
            (timeout != -1) ? timeout : turnPID.defaultTimeout
        );

        while(!(this->turnPID.isSettled())) {
            float error = targetHeading - this->getAvgHeading();
            float power = this->turnPID.compute(error);

            leftMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;
            rightMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;

            pros::delay(10);
        }


        driveMotors.brake();
        this->turnPID.resetSystem();
    }

    // Relative turns are just absolute turns from the current position, fetched with getAvgHeading()
    void Chassis::turnToAngleRelative(double targetAngle, double maxPower, double settleTime, double settleRange, double timeout) {
        this->turnToHeading(getAvgHeading() + targetAngle, maxPower, settleTime, settleRange, timeout);
    }
}