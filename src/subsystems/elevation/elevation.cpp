#include "globals.hpp"
#include "main.h"
#include "pros/motors.h"

namespace subsystems {

    Elevation::Elevation(char ADIport) : elevation(ADIport) {}

    void Elevation::runOpcontrol() {
        if(inputSystem.getElevationNewPress()) toggleElevation();
    }
}