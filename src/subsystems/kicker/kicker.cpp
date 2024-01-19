#include "globals.hpp"
#include "main.h"

namespace subsystems {

    Kicker::Kicker(int portLeft, int portRight, int opticalSensorPort, int kickerRotationPort, double chargedAngle = 30) : 
        rightMotor(portRight, pros::E_MOTOR_GEAR_GREEN, true, pros::E_MOTOR_ENCODER_COUNTS),
        leftMotor(portLeft, pros::E_MOTOR_GEAR_RED, true, pros::E_MOTOR_ENCODER_COUNTS), 
        kickerOpticalSensor(opticalSensorPort),
        kickerRotationSensor(kickerRotationPort),
        kickerMotors({rightMotor, leftMotor}),
        kickerPID(0, 0.1, 0.2, 0, 0, 10 * 100, 500, 4000),
        CHARGED_POSITION_ANGLE(chargedAngle) {
            // kickerRotationSensor.reset();
            matchLoadRoutineIsActive = true;
        }

    void Kicker::chargeSync() {
        // TODO: Change to PID?
        int sensorProximity = kickerOpticalSensor.get_proximity();
        const int sensorThreshold = 210;

        float error = CHARGED_POSITION_ANGLE - kickerRotationSensor.get_position();
        float power = kickerPID.compute(error);


        if(sensorProximity > sensorThreshold) {
            kickerMotors = 127; // Fire Catapult
        } else {
            if(kickerRotationSensor.get_position() > CHARGED_POSITION_ANGLE || kickerRotationSensor.get_position() < 0){
                kickerMotors = 0;
            } else {
                kickerMotors = power;
            }
        }
    }


    void Kicker::runOpcontrol() {
        // if(inputSystem.getKickerToggleNewPress()) {
        //     matchLoadRoutineIsActive = !matchLoadRoutineIsActive;
        // }
        pros::screen::print(pros::E_TEXT_MEDIUM, 1, "kickerToggle: %d", matchLoadRoutineIsActive); 
        pros::screen::print(pros::E_TEXT_MEDIUM, 3, "rot: %d", kickerRotationSensor.get_position()); 


        if(matchLoadRoutineIsActive) {
            chargeSync();
        } else {
            // Kicker is lowered & matchloading gets disabled - run motors until the kicker returns to its home position
            // if(kickerRotationSensor.get_position() < 5) kickerMotors = 127;
        }
    }

    
}