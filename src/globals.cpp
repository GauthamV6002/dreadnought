#include "main.h" 

namespace subsystems {
    InputSystem inputSystem(pros::E_CONTROLLER_MASTER);
    
    // TODO: Fix Sensor Ports
    Kicker kicker(10, 2, 5, 19, 6300);
    Intake intake(20, 19, 20);

    Wings wings('A', 'B');
    Elevation elevation('H');

    Chassis chassis(
        16, 
        18, 
        9,
        13, 
        14, 
        3,
        7,
        17
    );
}