#include "globals.hpp"
#include "main.h"

namespace subsystems {

    // Raise/Lower
    void Elevation::raiseElevation() {
        verticalHang.set_value(HIGH);
    }

    void Elevation::closeElevation() {
        verticalHang.set_value(LOW);
    }

    void Elevation::openBalanceHang() {
        balanceHang.set_value(HIGH);
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