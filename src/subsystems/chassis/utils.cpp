#include "main.h"

namespace subsystems {
    void Chassis::tarePosition() {
        driveMotors.tare_position();
    }

    float Chassis::getAvgEncoderValue() {
        return (frontLeft.get_position() + middleLeft.get_position() + backLeft.get_position() + frontRight.get_position() + middleRight.get_position() + backRight.get_position()) / 6.0;
    }

    float Chassis::getAvgHeading() {
        if(IMUFront.get_rotation() == PROS_ERR_F) return IMUFront.get_rotation();
        if(IMUBack.get_rotation() == PROS_ERR_F) return IMUBack.get_rotation();
        else return ((IMUBack.get_rotation() + IMUFront.get_rotation()) / 2);
    }
}