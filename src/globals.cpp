#include "autonlib/autonlib.hpp"
#include "main.h" 


namespace subsystems {
    autonlib::AutonManager autonManager('H');
    InputSystem inputSystem(pros::E_CONTROLLER_MASTER);
    
    Kicker kicker(10, 2, 5, 3, 5700);
    Intake intake(19, 11, 'B', 0, 20);

    Wings wings('A', 'G'); // Back Wings not used
    Elevation elevation('C', 'D');

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