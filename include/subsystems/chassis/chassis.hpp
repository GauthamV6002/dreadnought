#ifndef __CHASSIS
#define __CHASSIS

#include "api.h"
#include "pros/imu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

#include "PID/PID.hpp"


namespace subsystems {

    enum E_SWING_TYPE {
        SWING_RIGHT = 1, SWING_LEFT = -1
    };

    class Chassis {

        public:

        // Size Constants
        float DRIVE_WIDTH = 11.5;
        float DRIVE_LENGTH = 12.5;

        // Drive
        pros::Motor frontLeft;
        pros::Motor middleLeft;
        pros::Motor backLeft;
        pros::Motor frontRight;
        pros::Motor middleRight;
        pros::Motor backRight;

        pros::Motor_Group leftMotors;
        pros::Motor_Group rightMotors;
        pros::Motor_Group driveMotors;

        // IMUs
        pros::IMU IMUFront;
        pros::IMU IMUBack;

        // PID Systems
        PID::PID_System drivePID;
        PID::PID_System turnPID;
        PID::PID_System swingAnglePID;

        // PID Stall & Quick Transition Detection Constants
        const int MIN_LATERAL_MOVE_POWER = 10;
        const int MIN_TURN_MOVE_POWER = 20;
        const int MIN_SWING_MOVE_POWER = 20;

        const int MIN_STALL_TIME = 600;
        const int MIN_STALL_VELOCITY = 70;

        const int QUICK_TRANSITION_TIME = 40;

        // Drive Constants
        const double JOYSTICK_TURN_GAIN = 2.5;
        const int JOYSTICK_DEADZONE = 5;
        const float TRACTION_TURN_MULTIPLIER = 1.75;

        // Todo: Add Odom Object

        public:
            Chassis(int frontLeftPort, int middleLeftPort, int backLeftPort, int frontRightPort, int middleRightPort, int backRightPort, int IMUFrontPort, int IMUBackPort);

            // Teleop
            void arcade(bool joystickCurves, bool invertTurning, bool singeStick);
            void curvature();

            // Utils
            void tarePosition();
            void resetIMUs();
            void setBrakeMode(pros::motor_brake_mode_e_t brakeMode);

            float getAvgEncoderValue();
            float getAvgMotorVelocity();
            float getAvgHeading();
            double requestAvgIMUHeading();


            
            // Auton
            // Simple PID Movement Functions
            void moveLateral(int targetDistance, double maxPower = 127, double settleTime  = -1, double settleRange  = -1, double timeout = -1);
            void turnToAngleRelative(double targetAngle, double maxPower = 127, double settleTime = -1, double settleRange  = -1, double timeout  = -1);
            void swingToAngleRelative(double targetAngle, E_SWING_TYPE swingType, double maxPower= 127, double settleTime = -1, double settleRange = -1, double timeout = -1);


            // Arc Turns
            void arcTurnToAngle(double targetAngle, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
            void arcTurnToHeading(double targetHeading, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
            void arcTurnDistance(double distance, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);

            // Functions utilizing odometry/global turns
            void moveToPoint(double x, double y, double heading, double maxLateralPower, double maxTurnPower, double lateralSettleTime, double lateralSettleRange);
            void turnToHeading(double targetHeading, double maxPower = 127, double settleTime = -1, double settleRange  = -1, double timeout  = -1);
            void swingToHeading(double targetHeading, E_SWING_TYPE swingType, double maxPower = 127, double settleTime = -1, double settleRange = -1, double timeout = -1);
    };
}

#endif // __CHASSIS