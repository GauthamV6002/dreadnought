#include "main.h"

autonlib::Routine::Routine(std::string name, float startX, float startY, float startHeading, Callback driveRoute)
    : routineName(name), startX(startX), startY(startY), startHeading(startHeading), driveRoute(driveRoute) {}

void autonlib::Routine::setupRoutine() {
    // Maybe check if pos doesn't exist, if it does, then use current odom pos
    // odom.setPos(x, y, heading);
}

void autonlib::Routine::runRoutine() {
    setupRoutine();
    driveRoute();
}