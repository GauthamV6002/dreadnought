#include "main.h"
#include "okapi/api/util/mathUtil.hpp"
#include "utils/math/math.hpp"

namespace subsystems {

    void Chassis::setPose(double x, double y, double heading) {
        currentX = x;
        currentY = y;
        currentHeading = heading;
    }

    void Chassis::setPose(double x, double y) {
        currentX = x;
        currentY = y;
    }

    void Chassis::turnTowardsPoint(double x, double y, double maxPower, bool reverse, double settleTime, double settleRange, double timeout) {
        odomMutex.take();
        float angle = utils::radToDeg(atan2(y - currentY, x - currentX));
        if (angle < 0.5) {
            odomMutex.give();
            return;
        }
        float heading = utils::get0to360Angle(angle);
        float imu = utils::getShortestTurn(heading, currentHeading, reverse);
        odomMutex.give(); // Open Mutex before the blocking task
        
        chassis.turnToHeading(imu, maxPower, settleTime, settleRange, timeout);
    }

    void Chassis::turnBacksideTowardsPoint(double x, double y, double maxPower, bool reverse, double settleTime, double settleRange, double timeout) {
        odomMutex.take();
        float angle = utils::radToDeg(atan2(y - currentY, x - currentX));
        if (angle < 0.5) {
            odomMutex.give();
            return;
        }
        float heading = utils::get0to360Angle(angle);
        float imu = utils::getShortestTurn(heading + 180, currentHeading, reverse);
        odomMutex.give(); // Open Mutex before the blocking task

        chassis.turnToHeading(imu, maxPower, settleTime, settleRange, timeout);
    }



    // Point-and-Shoot Movement (no curves)
    void Chassis::moveToPoint(double x, double y, double maxTurnPower, bool turnReversed, double maxLateralPower, double lateralSettleTime, double lateralSettleRange) {
        // Turn towards point
        chassis.turnTowardsPoint(x, y, maxTurnPower, turnReversed);
        
        // Linear Motion towards point
        odomMutex.take();
        double dist = utils::euclideanDistance(x, y, currentX, currentY);
        odomMutex.give();

        chassis.moveLateral(fabs(dist), maxLateralPower);
        
        // Psuedo-Odom
        // if(!odomEnabled) setPose(x, y, requestAvgIMUHeading());
    }

    void Chassis::moveToPointBackwards(double x, double y, double maxTurnPower, bool turnReversed, double maxLateralPower, double lateralSettleTime, double lateralSettleRange) {
        // Turn towards point
        chassis.turnBacksideTowardsPoint(x, y, maxTurnPower, turnReversed);
        
        // Linear Motion towards point
        odomMutex.take();
        double dist = utils::euclideanDistance(x, y, currentX, currentY);
        odomMutex.give();

        chassis.moveLateral(-fabs(dist), maxLateralPower);
        // if(!odomEnabled) setPose(x, y, requestAvgIMUHeading());
    }

}