#include "globals.hpp"
#include "main.h"

namespace subsystems {

    // Set controller up
    Wings::Wings(char frontWingsPort, char backWingsPort) : 
        frontWings(frontWingsPort, LOW), 
        backWings(backWingsPort, LOW) {}

    // Opcontrol
    void Wings::runOpcontrol() {
        if(inputSystem.getFrontWingsPressed()) openFrontWings();
        else closeFrontWings();
    }
}