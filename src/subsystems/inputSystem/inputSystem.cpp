#include "inputSystem.hpp"
#include "main.h"
#include "pros/misc.h"

namespace subsystems {

    // Set controller up
    InputSystem::InputSystem(pros::controller_id_e_t controllerID) : master(controllerID) {}

    // Controller Vibration
    void InputSystem::rumbleController(const char *rumble_pattern) {
        master.rumble(rumble_pattern);
    }


    // Chassis
    int InputSystem::getChassisThrottle() { 
        return master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_Y); 
    }

    int InputSystem::getChassisTurnPower(bool singleStick) { 
        return (singleStick ? master.get_analog(pros::E_CONTROLLER_ANALOG_LEFT_X) : master.get_analog(pros::E_CONTROLLER_ANALOG_RIGHT_X));
    }

    
    // Kicker/Intake
    int InputSystem::getIntakeState() { 
        if(master.get_digital(pros::E_CONTROLLER_DIGITAL_R2)) return 1;
        else if(master.get_digital(pros::E_CONTROLLER_DIGITAL_L2)) return -1;
        else return 0;
    }

    bool InputSystem::getKickerToggleNewPress() {
        return master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_Y);
    }

    bool InputSystem::getManualKickerPressed() {
        return master.get_digital(pros::E_CONTROLLER_DIGITAL_DOWN);
    }
    

    // Solenoids
    bool InputSystem::getFrontWingsPressed() {
        return master.get_digital(pros::E_CONTROLLER_DIGITAL_R1);
    }

    bool InputSystem::getIntakeLiftRaised() {
        return master.get_digital(pros::E_CONTROLLER_DIGITAL_L1);
    }

    bool InputSystem::getElevationNewPress() {
        bool b_pressed = master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_B);
        return b_pressed;
    }

    bool InputSystem::getBalanceHangShouldOpen() {
        bool down_pressed = master.get_digital_new_press(pros::E_CONTROLLER_DIGITAL_DOWN);
        return down_pressed;
    }

    // Controller Feedback System
    void InputSystem::runControllerFeedback() {
        int timestamp = pros::millis();

        // Between the last 10 -> 9.5s, make the controller rumble to indicate its time for hang
        if(timestamp > 95*1000 && timestamp < 95.5*1000){
            rumbleController("..");
        }
    }

}