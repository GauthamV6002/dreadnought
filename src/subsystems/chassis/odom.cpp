#include "main.h"

namespace subsystems {

    void Chassis::initializeOdometry() {

    }

    void Chassis::updateOdometry() {

        // Get all IME & IMU Values, calculate left/right offsets
        float verticalIMELeftRaw = getLeftDistTravelled();
        float verticalIMERightRaw = getRightDistTravelled();
        currentHeading = getAvgHeading();

        float deltaVerticalIMELeft = verticalIMELeftRaw - prevLeftIMEDistTravelled;
        float deltaVerticalIMERight = verticalIMERightRaw - prevRightIMEDistTravelled;
        float deltaHeading = currentHeading - prevHeading;

        // Update prev values for next iteration - we can do this now because only deltas are used beyond this point
        prevLeftIMEDistTravelled = verticalIMELeftRaw;
        prevRightIMEDistTravelled = verticalIMERightRaw;
        prevHeading = currentHeading;

        // By default, for zero-tracker odom, right side of the drive becomes the main tracker
        // So we use deltaVerticalIMERight, and ignore horizontal tranlsations due to a lack of a horizontal tracker

        // calculate local x and y
        float localX = 0;
        float localY = 0;
        if (deltaHeading == 0) { // prevent divide by 0
            localX = 0;
            localY = deltaVerticalIMERight; // Using tractions, so assume no horizontal translation
        } else {
            localX = 0;
            localY = 2 * sin(deltaHeading / 2) * (deltaVerticalIMERight / deltaHeading + (DRIVE_WIDTH / 2));
        }

        // calculate global x and y

        float avgHeading = currentHeading + deltaHeading / 2;
        currentX += localY * sin(avgHeading);
        currentY += localY * cos(avgHeading);
        currentX += localX * -cos(avgHeading);
        currentY += localX * sin(avgHeading);


    }
}