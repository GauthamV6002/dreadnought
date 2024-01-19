#include "globals.hpp"
#include "main.h"

namespace subsystems {

    void Intake::setActiveHold(bool state, int power) {
        activeHold = state;
        activeHoldPower = power;
    }
    
    // Todo: other utils
    

    void Intake::setIntakeIn(int power = 127) {
        intakeMotor = power;
    }
}