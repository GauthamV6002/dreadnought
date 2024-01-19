#ifndef __WINGS
#define __WINGS

#include "api.h"
#include "pros/motors.hpp"

namespace subsystems {
    class Wings {
        pros::ADIDigitalOut backWings;
        pros::ADIDigitalOut frontWings;

        public:
            Wings(char frontWingsPort, char backWingsPort);

            // Teleop
            void runOpcontrol();
            
            // Auton
            void openFrontWings();
            void closeFrontWings();

            void openBackWings();
            void closeBackWings();

            void flickFrontWings(int millis);

    };
}

#endif // __WINGS