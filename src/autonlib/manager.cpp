#include "autonlib.hpp"
#include "main.h"

autonlib::AutonManager::AutonManager(char limitSwitchPort)
    : limitSwitchPort(limitSwitchPort) {}

void autonlib::AutonManager::addRoutine(Routine routine) {
    this->routines.push_back(routine);
    this->routineNames.push_back(routine.routineName);
}