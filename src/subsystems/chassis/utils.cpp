#include "main.h"

namespace subsystems {
    void Chassis::tarePosition() {
        driveMotors.tare_position();
    }

    void Chassis::resetIMUs() {
        IMUFront.reset(false);
        IMUBack.reset(false);
    }

    void Chassis::setBrakeMode(pros::motor_brake_mode_e_t brakeMode) {
        driveMotors.set_brake_modes(brakeMode);
    }


    // Motor/IME Utils

    double Chassis::inchesToCounts(float inches) {
        // counts = inches * 400/(2.75 * pi)
        return (inches * 46.29961);
    }
    double Chassis::countsToInches(float counts)  {
        // inches = counts / 400/(2.75 * pi)
        return (counts / 46.29961);
    }

    float Chassis::getAvgEncoderValue() {
        return (frontLeft.get_position() + middleLeft.get_position() + backLeft.get_position() + frontRight.get_position() + middleRight.get_position() + backRight.get_position()) / 6.0;
    }

    float Chassis::getAvgMotorVelocity() { 
        return (frontLeft.get_actual_velocity() + middleLeft.get_actual_velocity() + backLeft.get_actual_velocity() + frontRight.get_actual_velocity() + middleRight.get_actual_velocity() + backRight.get_actual_velocity()) / 6.0;
    }


    // Distance travelled by IMEs for each drive pod, used in odom calculations
    
    float Chassis::getLeftDistTravelled() {
        float imePos = (frontLeft.get_position() + middleLeft.get_position() + backLeft.get_position()) / 3.0;
        return countsToInches(imePos);
    }

    float Chassis::getRightDistTravelled() {
        float imePos = (frontRight.get_position() + middleRight.get_position() + backRight.get_position()) / 3.0;
        return countsToInches(imePos);
    }


    // IMU Utils

    float Chassis::getAvgHeading() {
        if(IMUFront.get_rotation() == PROS_ERR_F) return IMUBack.get_rotation();
        if(IMUBack.get_rotation() == PROS_ERR_F) return IMUFront.get_rotation();
        else return ((IMUBack.get_rotation() + IMUFront.get_rotation()) / 2);
    }

    // Blocks thread until the IMUs can return a value
    double Chassis::requestAvgIMUHeading() {
        while (true) {
            double rotationFront = IMUFront.get_rotation();
            double rotationBack = IMUBack.get_rotation();

            if (rotationFront != PROS_ERR_F && rotationBack != PROS_ERR_F) return (rotationFront + rotationBack) / 2;
            else if (rotationFront == PROS_ERR_F && rotationBack != PROS_ERR_F) return (rotationBack);
            else if (rotationBack == PROS_ERR_F && rotationFront != PROS_ERR_F) return (rotationFront);
            else pros::delay(50);
            pros::screen::print(TEXT_MEDIUM, 5, "IMU requested"); 
        }
    }

    void Chassis::enableOdometry() {
        odomEnabled = true;
    }

    void Chassis::disableOdometry() {
        odomEnabled = false;
    }
}