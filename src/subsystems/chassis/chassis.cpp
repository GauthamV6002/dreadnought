#include "globals.hpp"
#include "main.h"
#include "pros/imu.hpp"
#include "pros/motors.h"

namespace subsystems {

    Chassis::Chassis(int frontLeftPort, int middleLeftPort, int backLeftPort, int frontRightPort, int middleRightPort, int backRightPort, int IMUFrontPort, int IMUBackPort) :
        frontLeft (frontLeftPort, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS),
        middleLeft (middleLeftPort, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS),
        backLeft (backLeftPort, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS),
        frontRight (frontRightPort, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS),
        middleRight (middleRightPort, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS),
        backRight (backRightPort, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS),

        IMUFront(IMUFrontPort),
        IMUBack(IMUBackPort),

        leftMotors ({frontLeft, middleLeft, backLeft}),
        rightMotors ({frontRight, middleRight, backRight}),
        driveMotors ({frontLeft, middleLeft, backLeft, frontRight, middleRight, backRight}), 
        
        drivePID(0, 0.3, 0.0, 2.225, 250, 75, 50, 2500),
        turnPID(0, 3.0, 0.0, 17.5, 100, 7.0, 200.0, 4000),
        swingAnglePID(0, 5.0, 0.0, 28.0, 100, 5, 50, 2000)
        {}

    
    void Chassis::arcade(bool joystickCurves = false, bool invertTurning = false, bool singleStick = false) {
        int ithrottle = inputSystem.getChassisThrottle();
        int iturn = inputSystem.getChassisTurnPower(singleStick);
        
        if(invertTurning) iturn *= -1; // Invert turning if activated
        
        // Check if driver is turning in place
        bool turnInPlace = false;
        if(abs(iturn) < JOYSTICK_DEADZONE && abs(ithrottle) > JOYSTICK_DEADZONE) turnInPlace = true;

        // Deadzones
        if(abs(ithrottle) < JOYSTICK_DEADZONE) ithrottle = 0;
        if(abs(iturn) < JOYSTICK_DEADZONE) iturn = 0;

        // Remap turns with curves & non-in-place turns
        double turn = joystickCurves ? utils::exponentialInputRemap(iturn, JOYSTICK_TURN_GAIN) : iturn;
        if(!turnInPlace) turn *= TRACTION_TURN_MULTIPLIER;

        leftMotors = ithrottle + turn;
        rightMotors = ithrottle - turn;
    }

    void Chassis::curvature() {
        int ithrottle = inputSystem.getChassisThrottle();
        int iturn = inputSystem.getChassisTurnPower(false);

        if (ithrottle < JOYSTICK_DEADZONE) {
            arcade();
            return;
        }         

        float leftPower = ithrottle + (std::abs(ithrottle) * iturn) / 127.0;
        float rightPower = ithrottle - (std::abs(ithrottle) * iturn) / 127.0;

        leftPower = utils::exponentialInputRemap(leftPower, JOYSTICK_TURN_GAIN);
        rightPower = utils::exponentialInputRemap(rightPower, JOYSTICK_TURN_GAIN);

        leftMotors.move(leftPower);
        rightMotors.move(rightPower);
    }
}