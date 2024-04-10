#include "math.hpp"
#include <math.h>

const float PI = 3.14159265;
namespace utils {
    // For Joystick Curves
    float exponentialInputRemap(float input, float scale) {
        if (scale != 0) {
            return (powf(2.718, -(scale / 10)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(scale / 10)))) * input;
        }
        return input;
    }

    float sign(float value) {
        return ((value >= 0.0) ? 1.0 : -1.0);
    }

    // Angle Conversions
    float degToRad(float deg) {
        return (deg * PI / 180.0);
    }
    float radToDeg(float rad) {
        return (rad / PI * 180.0);
    }

    // For Odometry
    float euclideanDistance(float x1, float y1, float x2, float y2) {
        float diffX = x2 - x1; 
        float diffY = y2 - y1;

        return sqrt(diffX*diffX + diffY*diffY); 
    }

    float get0to360Angle(float angle) {
        double result = fmod(angle, 360.0);
        return result + (result < 0 ? 360.0 : 0.0);
    }

    float getShortestTurn(float targetHeading, float currentHeading, bool reverse) {
        float fullTurns =  currentHeading / 360.0;

        float upper = 360.0 * ceil(fullTurns) + targetHeading;
        float lower = 360.0 * floor(fullTurns) + targetHeading;

        if(abs(currentHeading - upper) > abs(currentHeading - lower)) return (reverse ? upper : lower);
        else return (reverse ? lower : upper);
    }
}