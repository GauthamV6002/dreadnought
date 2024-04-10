#include "main.h"
#include "subsystems/chassis/chassis.hpp"

namespace subsystems {
    
    void Chassis::swingToHeading(double targetHeading, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout) {


        swingAnglePID.setStopConditionConstants(
            (settleRange != -1) ? settleRange : swingAnglePID.defaultMinSettleError, 
            (settleTime != -1) ? settleTime : swingAnglePID.defaultMinSettleTime, 
            (timeout != -1) ? timeout : swingAnglePID.defaultTimeout
        );
        
        /*
            INCREASE && FWD => LEFT(+)
            INCREASE && BWD => RIGHT(-)
            DECREASE && FWD => RIGHT(+)
            DECREASE && BWD => LEFT(-)
        */
        bool headingIncreasing = (this->requestAvgIMUHeading() < targetHeading);

        while(!(this->swingAnglePID.isSettled())) {
            float error = targetHeading - this->requestAvgIMUHeading();
            float power = this->swingAnglePID.compute(error);

            // Clamp power if maxpower > power
            if(fabs(power) > fabs(maxPower)) power = utils::sign(power) * maxPower;

            if(swingType == SWING_LEFT) {
                leftMotors = power;
                rightMotors.brake();
            }
            else if (swingType == SWING_RIGHT) {
                rightMotors = -power;
                leftMotors.brake();
            }

            pros::delay(10);
        }

        driveMotors.brake();
        // pros::delay(20);
        this->swingAnglePID.resetSystem();
    }
}