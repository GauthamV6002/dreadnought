#ifndef __DISPLAY_LIB
#define __DISPLAY_LIB

#include "api.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_misc/lv_color.h"
#include "pros/misc.h"
#include "pros/misc.hpp"

namespace displaylib {
    // Shows the logo in the background
   void displayLogo();

   // Shows fields to left of the screen
   void displayMatchField();
   void displaySkillsField();

    // General Styling
    void setBackgroundColor(lv_color32_t color);

    // Show Text
    void showCenterText(std::string text, int xOffset = 0, int yOffset = 0);

    // Widgets
    void animateSliderFor(int millis);
}

#endif // __DISPLAY_LIB