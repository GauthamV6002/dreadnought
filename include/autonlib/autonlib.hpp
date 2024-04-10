#ifndef __AUTON_LIB
#define __AUTON_LIB

#include "subsystems/chassis/chassis.hpp"
#include <functional>
#include <string>

namespace autonlib {

    // Macros for headings to make code a bit more readable
    enum HEADINGS {
        BOTTOM_LEFT = -135,
        LEFT = -90,
        TOP_LEFT = -45,
        UP = 0,
        TOP_RIGHT = 45,
        RIGHT = 90,
        BOTTOM_RIGHT = 135,
        DOWN = 180
    };


    class Routine {
        public:
            // Define a type alias for the callback function
            using Callback = std::function<void()>;
            Callback driveRoute;

            // Other Info about the Routine
            float startX = 0.0, startY = 0.0, startHeading = 0.0;
            std::string routineName = "default";

            // Routine Constructor takes a driveRoute function as a callback
            Routine(std::string name, float startX, float startY, float startHeading, Callback driveRoute);

            void setupRoutine(subsystems::Chassis, bool smartStartEnabled = true);
            void runRoutine(subsystems::Chassis chassis, bool smartStartEnabled);
    };

    class AutonManager {
        public:
            AutonManager(char limitSwitchPort);

            void addRoutine(Routine routine);

            void runRoutine(std::string routineName);
            std::string getSelectedRoutine();

            void displaySelectionOnBrain();

            // Initialize Routes
            void initCloseSideRoutines();
            void initFarSideRoutines();

        private:
            char limitSwitchPort;
            std::vector<Routine> routines;
            std::vector<std::string> routineNames;
    };

    extern AutonManager auto_manage;
}

#endif // __AUTON_LIB