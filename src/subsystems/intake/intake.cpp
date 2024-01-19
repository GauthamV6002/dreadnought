#include "globals.hpp"
#include "main.h"
#include "pros/motors.h"

namespace subsystems {

    Intake::Intake(int motorPort, int sensorPort, int intakeDistanceThreshold = 20) :
        intakeMotor(motorPort, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS),
        intakeDistanceSensor(sensorPort),
        INTAKE_DISTANCE_THRESHOLD(intakeDistanceThreshold) 
        /* Constructor Definition */ {
            intakeMotor.set_brake_mode(pros::E_MOTOR_BRAKE_HOLD);
        }


    void Intake::runOpcontrol() {

        int intakeState = inputSystem.getIntakeState();

        if(inputSystem.getIntakeState() != 0) {
            setIntakeIn(127 * intakeState);

        } else {
            // If there is a triball in the intake, run activeHold if enabled
            if(activeHold) setIntakeIn(activeHoldPower);
            else intakeMotor.brake();
        }

    }
}