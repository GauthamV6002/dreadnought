#include "autonlib.hpp"
#include "main.h"
#include "subsystems/chassis/chassis.hpp"

autonlib::Routine::Routine(std::string name, float startX, float startY, float startHeading, Callback driveRoute, ROUTINE_TYPE type)
    : routineName(name), startX(startX), startY(startY), startHeading(startHeading), driveRoute(driveRoute), routineType(type) {}

void autonlib::Routine::runRoutine(subsystems::Chassis chassis, bool smartStartEnabled) {
    if(smartStartEnabled) {
        chassis.setPose(startX, startY, chassis.requestAvgIMUHeading());
        chassis.imuOffset = 0;
    } else {
        // TODO: Make imuOffset work fully
        chassis.setPose(startX, startY, startHeading);
        chassis.imuOffset = startHeading;
    }

    driveRoute();
}