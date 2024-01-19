#ifndef __INTAKE
#define __INTAKE

#include "api.h"
#include "pros/distance.hpp"
#include "pros/motors.hpp"

namespace subsystems {
    class Intake {
        pros::Motor intakeMotor;
        pros::Distance intakeDistanceSensor;

        bool activeHold = false;
        int activeHoldPower = 80;

        int INTAKE_DISTANCE_THRESHOLD = 20;

        public:
            Intake(int motorPort, int sensorPort, int intakeDistanceThreshold);

            // Teleop
            void runOpcontrol();
            
            // Auton

            void setActiveHold(bool state, int power);

            void setIntakeIn(int power);
            void intakeTriball(int millis); // Blocking, full intake
            void outtakeTriball(int power, int millis); // Blocking, full outtake

            void intakeFully(int millis); // Blocking, full smart intake
    };
}

#endif // __INTAKE