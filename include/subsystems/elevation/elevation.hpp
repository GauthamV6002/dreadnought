#ifndef __ELEVATION
#define __ELEVATION

#include "api.h"
#include "pros/motors.hpp"

namespace subsystems {
    class Elevation {
        pros::ADIDigitalOut verticalHang;
        pros::ADIDigitalOut balanceHang;

        bool elevationIsRaised = false;

        public:
            Elevation(char verticalHangPort, char balanceHangPort);

            // Teleop
            void runOpcontrol();
            
            // Auton - Vertical Hang
            void raiseElevation();
            void closeElevation();

            // Balance
            void openBalanceHang();

            // Driver - Vertical Hang
            void toggleElevation();
    };
}

#endif // __ELEVATION