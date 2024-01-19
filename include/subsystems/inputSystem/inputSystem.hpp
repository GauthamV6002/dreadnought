#ifndef __INPUT_SYS
#define __INPUT_SYS

#include "api.h"
#include "pros/misc.h"
#include "pros/misc.hpp"

namespace subsystems {
    class InputSystem {
        pros::Controller master;

        public:
            InputSystem(pros::controller_id_e_t controllerID);

            // Chassis
            int getChassisThrottle();
            int getChassisTurnPower(bool singleStick);

            
            // Kicker/Intake
            int getIntakeState(); // 1 is intake inwards, 0 is hold, -1 is intake outwards
            bool getKickerToggleNewPress();
            
            // Pistons
            bool getFrontWingsPressed();
            bool getBackWingsPressed();
            bool getElevationNewPress();

    };
}

#endif // __INPUT_SYS