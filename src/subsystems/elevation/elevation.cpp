#include "globals.hpp"
#include "main.h"
#include "pros/motors.h"

namespace subsystems {

    Elevation::Elevation(char verticalHangPort, char balanceHangPort) : verticalHang(verticalHangPort), balanceHang(balanceHangPort) {}

    void Elevation::runOpcontrol() {
        if(inputSystem.getElevationNewPress()) toggleElevation();
        if(inputSystem.getBalanceHangShouldOpen()) openBalanceHang();
    }
}