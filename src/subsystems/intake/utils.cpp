#include "globals.hpp"
#include "main.h"

namespace subsystems {

    void Intake::setActiveHold(bool state, int power) {
        activeHold = state;
        activeHoldPower = power;
    }
    
    void Intake::setIntakeIn(int power = 127) {
        intakeMotors = -power;
    }

    void Intake::outtakeTriballFor(int millis, int power) {
        setIntakeIn(abs(power) * -1);
        pros::delay(millis);
        intakeMotors.brake();
        setIntakeIn(0);
    }

    void Intake::intakeTriballFor(int millis, int power) {
        setIntakeIn(abs(power));
        pros::delay(millis);
        intakeMotors.brake();
        setIntakeIn(0);
    }

    // Intake Lift

    void Intake::raiseIntake() {
        intakeLift.set_value(HIGH);
        intakeIsRaised = true;
    }

    void Intake::lowerIntake() {
        intakeLift.set_value(LOW);
        intakeIsRaised = false;
    }

    void Intake::toggleIntakeLift() {
        if(intakeIsRaised) {
            lowerIntake();
            intakeIsRaised = false;
        }
        else {
            raiseIntake();
            intakeIsRaised = true;   
        }

    }
}