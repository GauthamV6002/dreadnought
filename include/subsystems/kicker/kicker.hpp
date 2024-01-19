#ifndef __KICKER
#define __KICKER

#include "PID/PID.hpp"
#include "api.h"
#include "pros/motors.hpp"
#include "pros/optical.hpp"
#include "pros/rotation.hpp"

namespace subsystems {
    class Kicker {
        int CHARGED_POSITION_ANGLE;
        pros::Motor leftMotor, rightMotor; // From looking a the back of the robot
        pros::Motor_Group kickerMotors;

        // Sensors
        pros::Optical kickerOpticalSensor;
        pros::Rotation kickerRotationSensor;

        PID::PID_System kickerPID;

        // Kicker State
        bool matchLoadRoutineIsActive = false;

        public:
            Kicker(int portLeft, int portRight, int opticalSensorPort, int kickerRotationPort, double chargedAngle);

            // Teleop
            void runOpcontrol();
            void runMatchLoadRoutine();
            void returnToHome();

            // utils
            void resetRotationSensor();
            

            // Auton
            void charge();
            void chargeAsync(); // Non-blocking
            void chargeSync(); // Part of the global loop

            void fireKicker();
    };
}

#endif // __KICKER