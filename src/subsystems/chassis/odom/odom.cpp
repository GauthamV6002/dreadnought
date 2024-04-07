#include "main.h"

namespace subsystems {

    void Chassis::initializeOdometry() {
        currentX = 0.0;
        currentY = 0.0;
        currentHeading = 0.0;
        resetIMUs();
    }

    void Chassis::updateOdometry(void* param) {

        // Get all IME & IMU Values, calculate left/right offsets
        float verticalIMELeftRaw = getLeftDistTravelled();
        float verticalIMERightRaw = getRightDistTravelled();
        currentHeading = requestAvgIMUHeading(); // In degrees
        float deltaVerticalIMELeft = verticalIMELeftRaw - prevLeftIMEDistTravelled;
        float deltaVerticalIMERight = verticalIMERightRaw - prevRightIMEDistTravelled;
        float deltaHeading = utils::degToRad(currentHeading - prevHeading); // IN RADIANS

        // Update prev values for next iteration - we can do this now because only deltas are used beyond this point
        prevLeftIMEDistTravelled = verticalIMELeftRaw;
        prevRightIMEDistTravelled = verticalIMERightRaw;
        prevHeading = currentHeading; // Headings are in degrees, the DELTAS are in radianss

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

        pros::screen::print(TEXT_MEDIUM, 5, "localX: %f", localX); 
        pros::screen::print(TEXT_MEDIUM, 6, "localY: %f", localY); 

        // Calculate global x and y
        float avgHeading = utils::degToRad(currentHeading) + deltaHeading / 2;
        currentX += localY * sin(avgHeading);
        currentY += localY * cos(avgHeading);
        currentX += localX * -cos(avgHeading);
        currentY += localX * sin(avgHeading);

        pros::screen::print(TEXT_MEDIUM, 0, "currentX: %f", currentX); 
        pros::screen::print(TEXT_MEDIUM, 1, "currentY: %f", currentY); 
        pros::screen::print(TEXT_MEDIUM, 2, "currentHeading: %f", currentHeading); 
    }

        // Static member function to serve as the task entry point
    void Chassis::staticUpdateOdometry(void* param) {
        Chassis* chassis = static_cast<Chassis*>(param); // Convert the void pointer back to Chassis object
        
        while (true) {
            chassis->updateOdometry(nullptr);
            pros::delay(10);
        }
    }

    void Chassis::startOdometryTask() {
        initializeOdometry();
        pros::Task odomTask(staticUpdateOdometry, this);
    }
}