#ifndef __GLOBALS
#define __GLOBALS

#include "api.h"
#include "subsystems/chassis/chassis.hpp"
#include "subsystems/elevation/elevation.hpp"
#include "subsystems/inputSystem/inputSystem.hpp"
#include "subsystems/intake/intake.hpp"
#include "subsystems/kicker/kicker.hpp"
#include "subsystems/wings/wings.hpp"
#include "autonlib/autonlib.hpp"

namespace subsystems {
    extern InputSystem inputSystem;
    extern autonlib::AutonManager autonManager;
    
    extern Kicker kicker;
    extern Intake intake;

    extern Wings wings;
    extern Elevation elevation;

    extern Chassis chassis;
}

#endif