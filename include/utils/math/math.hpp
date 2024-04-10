#ifndef __MATH_UTILS
#define __MATH_UTILS

namespace utils {

    float exponentialInputRemap(float input, float scale);
    float sign(float value);

    float degToRad(float deg);
    float radToDeg(float rad);

    float euclideanDistance(float x1, float y1, float x2, float y2);
    float get0to360Angle(float angle);

    float getShortestTurn(float targetHeading, float currentHeading, bool reverse = false);
}

#endif // __MATH_UTILS