#include "main.h" 

namespace subsystems {
    InputSystem inputSystem(pros::E_CONTROLLER_MASTER);
    
    // TODO: Fix Sensor Ports
    Kicker kicker(10, 2, 5, 19, 5700);
    Intake intake(9, 0, 20);

    Wings wings('B', 'C');
    Elevation elevation('A');

    Chassis chassis(
        18, 
        17, 
        16,
        13, 
        14, 
        15,
        12,
        20
    );
}