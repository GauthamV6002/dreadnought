#include "globals.hpp"
#include "main.h"

namespace subsystems {

    // Blocking Function
    void Kicker::charge() {

    }

    void Kicker::resetRotationSensor() {
        kickerRotationSensor.reset_position();
    }

    // TODO: void Kicker::chargeAsync();
    

    void Kicker::fireKicker() {
        kickerMotors = 127;
        pros::delay(150);
    }

    
}