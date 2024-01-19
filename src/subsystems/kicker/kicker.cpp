#include "globals.hpp"
#include "main.h"

namespace subsystems {

    Kicker::Kicker(int portLeft, int portRight, int opticalSensorPort, int kickerRotationPort, double chargedAngle = 5500) : 
        rightMotor(portRight, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS),
        leftMotor(portLeft, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_COUNTS), 
        kickerOpticalSensor(opticalSensorPort),
        kickerRotationSensor(kickerRotationPort),
        kickerMotors({rightMotor, leftMotor}),
        kickerPID(0, 0.1, 0.2, 0, 0, 10 * 100, 500, 4000),
        CHARGED_POSITION_ANGLE(chargedAngle) {
        }

    void Kicker::chargeSync() {
        // TODO: Change to PID?
        int sensorProximity = kickerOpticalSensor.get_proximity();
        const int sensorThreshold = 210;

        float error = CHARGED_POSITION_ANGLE - kickerRotationSensor.get_position();
        float power = kickerPID.compute(error);

        pros::screen::print(pros::E_TEXT_MEDIUM, 6, "error: %f", error); 
        pros::screen::print(pros::E_TEXT_MEDIUM, 7, "power: %f", power); 


        if(sensorProximity > sensorThreshold) {
            kickerMotors = 127; // Fire Catapult
        } else {
            if(kickerRotationSensor.get_position() > CHARGED_POSITION_ANGLE){
                kickerMotors = 0;
            } else {
                // Set motors to PID power
                if(power < 10) kickerMotors = 0; // Low power causes motor stalling
                else kickerMotors = fabs(power);
            }
        }
    }


    void Kicker::runOpcontrol() {
        if(inputSystem.getKickerToggleNewPress()) {
            matchLoadRoutineIsActive = !matchLoadRoutineIsActive;
        }
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "kickerToggle: %d", matchLoadRoutineIsActive); 
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "rot: %d", kickerRotationSensor.get_position()); 

        bool manualKickerPressed = inputSystem.getManualKickerPressed();

        if(matchLoadRoutineIsActive && !manualKickerPressed) {
            chargeSync();
        } else if (manualKickerPressed)  {
            kickerMotors = 127; // Pull Kicker down
        } else if (!matchLoadRoutineIsActive) {
            // Kicker is lowered & matchloading gets disabled - run motors until the kicker returns to its home position
            int pos = kickerRotationSensor.get_position();
            if(pos > 1000) kickerMotors = 80;
            else kickerMotors = 0;
        }
    }

    
}