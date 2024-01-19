#include "main.h"

namespace subsystems {

    // Front Wings
    void Wings::openFrontWings() {
        frontWings.set_value(HIGH);
    }

    void Wings::closeFrontWings() {
        frontWings.set_value(LOW);
    }

    // Back Wings
    void Wings::openBackWings() {
        backWings.set_value(HIGH);
    }

    void Wings::closeBackWings() {
        backWings.set_value(LOW);
    }


    // Flick Wings Macro
    void Wings::flickFrontWings(int millis = 400) {
        openFrontWings();
        pros::delay(millis);
        closeFrontWings();
    }
}