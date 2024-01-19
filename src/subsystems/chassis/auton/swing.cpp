// #include "main.h"

// namespace subsystems {
    
//     void Chassis::swingDistance(int targetDistance, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout)

//         turnPID.setStopConditionConstants(
//             (settleRange != -1) ? settleRange : turnPID.defaultMinSettleError, 
//             (settleTime != -1) ? settleTime : turnPID.defaultMinSettleTime, 
//             (timeout != -1) ? timeout : turnPID.defaultTimeout
//         );

//         while(!(this->turnPID.isSettled())) {
//             float error = targetHeading - this->getAvgHeading();
//             float power = this->turnPID.compute(error);

//             leftMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;
//             rightMotors = (fabs(power) > fabs(maxPower)) ? (fabs(maxPower) * utils::sign(power)) : power;

//             pros::delay(10);
//         }


//         driveMotors.brake();
//         this->turnPID.resetSystem();
//     }

// }