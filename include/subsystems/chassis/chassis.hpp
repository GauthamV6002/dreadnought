#ifndef __CHASSIS
#define __CHASSIS

#include "api.h"
#include "pros/imu.hpp"
#include "pros/motors.h"
#include "pros/motors.hpp"

#include "PID/PID.hpp"
#include "pros/rtos.hpp"


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

        float imuOffset = 0;

        /* SECTION - STALL DETECTION CONSTANTS */
        const int MIN_LATERAL_MOVE_POWER = 10;
        const int MIN_TURN_MOVE_POWER = 20;
        const int MIN_SWING_MOVE_POWER = 20;

        const int MIN_STALL_TIME = 600;
        const int MIN_STALL_VELOCITY = 30;

        const int QUICK_TRANSITION_TIME = 40;

        /* SECTION - TELEOP JOYSTICK CONSTANTS */
        const double JOYSTICK_TURN_GAIN = 2.5;
        const int JOYSTICK_DEADZONE = 5;
        const float TRACTION_TURN_MULTIPLIER = 1.4; // Previously 1.3
            
        Chassis(int frontLeftPort, int middleLeftPort, int backLeftPort, int frontRightPort, int middleRightPort, int backRightPort, int IMUFrontPort, int IMUBackPort);

        /* SECTION - TELEOP CONTROL SCHEMES */
        void arcade(bool joystickCurves, bool invertTurning, bool singeStick);
        void curvature();

        /* SECTION - SENSOR UTILITIES */
        void tarePosition();
        void resetIMUs();
        void setBrakeMode(pros::motor_brake_mode_e_t brakeMode);

        double countsToInches(float counts);
        double inchesToCounts(float inches);

        float getAvgEncoderValue();
        float getAvgMotorVelocity();
        float getAvgHeading();
        double requestAvgIMUHeading();

        float getLeftDistTravelled();
        float getRightDistTravelled();

        /* SECTION - PID MOVEMENT */
        // Simple PID Movement Functions
        void moveLateral(int targetDistance, double maxPower = 127, double settleTime  = -1, double settleRange  = -1, double timeout = -1);
        void turnToAngleRelative(double targetAngle, double maxPower = 127, double settleTime = -1, double settleRange  = -1, double timeout  = -1);
        void swingToAngleRelative(double targetAngle, E_SWING_TYPE swingType, double maxPower= 127, double settleTime = -1, double settleRange = -1, double timeout = -1);

        // Global Heading Based Turns
        void turnToHeading(double targetHeading, double maxPower = 127, double settleTime = -1, double settleRange  = -1, double timeout  = -1);
        void swingToHeading(double targetHeading, E_SWING_TYPE swingType, double maxPower = 127, double settleTime = -1, double settleRange = -1, double timeout = -1);

        // Arc Turns
        void arcTurnToAngle(double targetAngle, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
        void arcTurnToHeading(double targetHeading, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);
        void arcTurnDistance(double distance, double radius, E_SWING_TYPE swingType, double maxPower, double settleTime, double settleRange, double timeout);


        /* SECTION - ODOMETRY */
        // For Odom Task
        double currentX = 0.0, currentY = 0.0, currentHeading = 0.0;
        double prevX = 0.0, prevY = 0.0, prevHeading = 0.0;
        double prevLeftIMEDistTravelled = 0.0, prevRightIMEDistTravelled = 0.0;

        pros::Mutex odomMutex;
        bool odomEnabled = false;

        void enableOdometry();
        void disableOdometry();
        void initializeOdometry();

        void startOdometryTask();
        void updateOdometry(void* param);
        static void staticUpdateOdometry(void* param);

        // Movement Using Odom
        void moveToPoint(double x, double y, double maxTurnPower = 127, bool turnReversed = false, double maxLateralPower = -1, double lateralSettleTime = -1, double lateralSettleRange = -1);
        void moveToPointBackwards(double x, double y, double maxTurnPower = 127, bool turnReversed = false, double maxLateralPower = -1, double lateralSettleTime = -1, double lateralSettleRange = -1);
        void turnBacksideTowardsPoint(double x, double y, double maxPower = 127, bool reverse = false, double settleTime = -1, double settleRange  = -1, double timeout  = -1);
        void turnTowardsPoint(double x, double y, double maxPower = 127, bool reverse = false, double settleTime = -1, double settleRange  = -1, double timeout  = -1);

        void setPose(double x, double y, double heading);
        void setPose(double x, double y);

        
        /* SECTION - MACROS */
        void ramAndGoBack(double delay, double power, double distBack = -1);
    
    };
}

#endif // __CHASSIS