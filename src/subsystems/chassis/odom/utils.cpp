#include "main.h"

namespace subsystems {

    // Point-and-Shoot Movement (no curves)
    void Chassis::moveToPoint(double x, double y, double heading, double maxLateralPower, double maxTurnPower, double lateralSettleTime, double lateralSettleRange) {
        currentX = 0.0;
        currentY = 0.0;
        resetIMUs();
    }

    // Boomerang Controller
    // void Chassis::moveToPointBoomerang(double x, double y, double heading, double speedFactor) {

    // }

}