#ifndef __CHASSIS
#define __CHASSIS

#include "api.h"
#include "pros/imu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

#include "PID/PID.hpp"


namespace subsystems {

    enum E_SWING_TYPE {
        SWING_FWD = 1, SWING_BWD = -1
    };

    class Chassis {

        // Size Constants
        float DRIVE_WIDTH = 15.5;
        float DRIVE_LENGTH = 16.5;

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

        // Joystick Curve Constants
        const double JOYSTICK_TURN_GAIN = 2.5;
        const int JOYSTICK_DEADZONE = 5;

        // Todo: Add Odom Object

        public:
            Chassis(int frontLeftPort, int middleLeftPort, int backLeftPort, int frontRightPort, int middleRightPort, int backRightPort, int IMUFrontPort, int IMUBackPort);

            // Teleop
            void arcade(bool joystickCurves, bool invertTurning);
            void curvature();

            // Utils
            void tarePosition();
            float getAvgEncoderValue();
            float getAvgHeading();

            
            // Auton
            // Simple PID Movement Functions
            void moveLateral(int targetDistance, double maxPower, double settleTime, double settleRange, double timeout);
            void turnToAngleRelative(double targetAngle, double maxPower, double settleTime, double settleRange, double timeout);

            void swingDistance(int targetDistance, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
            void swingToAngle(double targetAngle, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);

            // Arc Turns
            void arcTurnToAngle(double targetAngle, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
            void arcTurnToHeading(double targetHeading, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
            void arcTurnDistance(double distance, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);

            // Functions utilizing odometry
            void moveToPoint(double x, double y, double heading, double maxLateralPower, double maxTurnPower, double lateralSettleTime, double lateralSettleRange);
            void turnToHeading(double targetHeading, double maxPower, double settleTime, double settleRange, double timeout);
    };
}

#endif // __CHASSIS