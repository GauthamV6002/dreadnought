#ifndef __ELEVATION
#define __ELEVATION

#include "api.h"
#include "pros/motors.hpp"

namespace subsystems {
    class Elevation {
        pros::ADIDigitalOut elevation;

        bool elevationIsRaised = false;

        public:
            Elevation(char ADIport);

            // Teleop
            void runOpcontrol();
            
            // Auton
            void raiseElevation();
            void closeElevation();

            void toggleElevation();
    };
}

#endif // __ELEVATION