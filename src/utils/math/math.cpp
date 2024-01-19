#include <math.h>

namespace utils {
    float exponentialInputRemap(float input, float scale) {
        if (scale != 0) {
            return (powf(2.718, -(scale / 10)) + powf(2.718, (fabs(input) - 127) / 10) * (1 - powf(2.718, -(scale / 10)))) * input;
        }
        return input;
    }

    float sign(float value) {
        return ((value >= 0.0) ? 1.0 : -1.0);
    }
}