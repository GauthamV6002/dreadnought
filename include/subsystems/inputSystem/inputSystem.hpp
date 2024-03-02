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

            // Controller Vibration
            void rumbleController(const char *rumble_pattern);

            // Chassis
            int getChassisThrottle();
            int getChassisTurnPower(bool singleStick);

            
            // Kicker/Intake
            int getIntakeState(); // 1 is intake inwards, 0 is hold, -1 is intake outwards
            bool getKickerToggleNewPress();
            bool getManualKickerPressed();
            
            // Wings
            bool getFrontWingsPressed();
            bool getBackWingsPressed();

            // Hang
            bool getElevationNewPress();
            bool getBalanceHangShouldOpen();

    };
}

#endif // __INPUT_SYS