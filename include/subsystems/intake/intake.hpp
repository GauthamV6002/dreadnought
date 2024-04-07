#ifndef __INTAKE
#define __INTAKE

#include "api.h"
#include "pros/adi.hpp"
#include "pros/distance.hpp"
#include "pros/motors.hpp"

namespace subsystems {
    class Intake {
        pros::Motor intakeMotorLeft;
        pros::Motor intakeMotorRight;
        pros::Motor_Group intakeMotors;
        pros::ADIDigitalOut intakeLift;
        pros::Distance intakeDistanceSensor;

        bool activeHold = false;
        int activeHoldPower = 80;

        int INTAKE_DISTANCE_THRESHOLD = 20;

        bool intakeIsRaised = true;

        public:
            Intake(int leftMotorPort, int rightMotorPort, char intakeLiftPort, int sensorPort, int intakeDistanceThreshold);

            // Teleop
            void runOpcontrol();
            
            // Auton
            void setActiveHold(bool state, int power);

            void setIntakeIn(int power);
            void intakeTriballFor(int millis = 500, int power = 127); // Blocking, full intake
            void outtakeTriballFor(int millis = 300, int power = 127); // Blocking, full outtake

            void intakeFully(int millis); // Blocking, full smart intake

            // Intake Lift
            void raiseIntake();
            void lowerIntake();
            void toggleIntakeLift();
    };
}

#endif // __INTAKE