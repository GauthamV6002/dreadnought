#include "globals.hpp"
#include "main.h"
#include "pros/motors.h"

namespace subsystems {

    Intake::Intake(int leftMotorPort, int rightMotorPort, char intakeLiftPort, int sensorPort, int intakeDistanceThreshold = 20) :
        intakeMotorLeft(leftMotorPort, pros::E_MOTOR_GEAR_BLUE, true, pros::E_MOTOR_ENCODER_COUNTS),
        intakeMotorRight(rightMotorPort, pros::E_MOTOR_GEAR_BLUE, false, pros::E_MOTOR_ENCODER_COUNTS),
        intakeMotors({intakeMotorLeft, intakeMotorRight}),
        intakeLift(intakeLiftPort, HIGH),
        intakeDistanceSensor(sensorPort),
        INTAKE_DISTANCE_THRESHOLD(intakeDistanceThreshold) 
        /* Constructor Definition */ {
            intakeMotors.set_brake_modes(pros::E_MOTOR_BRAKE_HOLD);
        }


    void Intake::runOpcontrol() {

        int intakeState = inputSystem.getIntakeState();

        if(inputSystem.getIntakeState() != 0) {
            setIntakeIn(127 * intakeState);

        } else {
            // If there is a triball in the intake, run activeHold if enabled
            if(activeHold) setIntakeIn(activeHoldPower);
            else intakeMotors.brake();

            if(inputSystem.getIntakeLiftLowered()) lowerIntake();
            else raiseIntake();
        }

    }
}