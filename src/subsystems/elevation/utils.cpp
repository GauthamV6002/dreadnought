#include "globals.hpp"
#include "main.h"

namespace subsystems {

    // Raise/Lower
    void Elevation::raiseElevation() {
        elevation.set_value(HIGH);
    }

    void Elevation::closeElevation() {
        elevation.set_value(LOW);
    }

    // Toggle Elevation
    void Elevation::toggleElevation() {
        if(elevationIsRaised) {
            closeElevation();
            elevationIsRaised = false;
        } else {
            raiseElevation();
            elevationIsRaised = true;
        }
    }
}