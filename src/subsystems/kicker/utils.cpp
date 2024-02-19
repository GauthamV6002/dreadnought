#include "globals.hpp"
#include "main.h"

namespace subsystems {

    void Kicker::resetRotationSensor() {
        kickerRotationSensor.reset_position();
    }

    void Kicker::fireNShots(int numShots, int timeout) {

        int timer = 0, shotsFired = 0;
        bool justFired = false;

        while(true) {
            bool kickerFired = chargeSync(); // Usually runs in main opcontrol loop, which is simulated here
            pros::delay(10);
            timer += 10;
            if(timer >= timeout) break;
            if(shotsFired >= numShots) break;

            // Incremental logic
            if(!justFired && kickerFired) {
                shotsFired++;
                justFired = true;
            } else if (!kickerFired) {
                justFired = false;
            }

        }
    }
    

    void Kicker::fireKicker() {
        kickerMotors = 127;
        pros::delay(150);
    }

    void Kicker::returnToHome() { 
        // Reset Kicker Pos
        int kickerPos = kicker.kickerRotationSensor.get_position();
        while (kickerPos > 1000) {
            kicker.kickerMotors = 80;
            kickerPos =  kicker.kickerRotationSensor.get_position();
            pros::delay(10);
        }
        kicker.kickerMotors = 0;
    }

    
}