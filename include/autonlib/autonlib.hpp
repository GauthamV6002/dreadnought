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

    enum ROUTINE_TYPE {
        CLOSE_SIDE = 1,
        FAR_SIDE = 2,
        SKILLS = 3
    };

    class Routine {
        public:
            // Define a type alias for the callback function
            using Callback = std::function<void()>;
            Callback driveRoute;

            // Other Info about the Routine
            float startX = 0.0, startY = 0.0, startHeading = 0.0;
            std::string routineName = "[default]";

            ROUTINE_TYPE routineType;

            std::string selectedAuton = "None";

            // Routine Constructor takes a driveRoute function as a callback
            Routine(std::string name, float startX, float startY, float startHeading, Callback driveRoute, ROUTINE_TYPE type);

            void setupRoutine(subsystems::Chassis, bool smartStartEnabled = true);
            void runRoutine(subsystems::Chassis chassis, bool smartStartEnabled);
    };

    class AutonManager {
        public:
            AutonManager(char limitSwitchPort);

            void addRoutine(Routine routine);

            void runRoutine(std::string routineName);
            std::string getSelectedRoutine();

            void displaySelector();
            void smartStartInit();

            // Initialize Routes
            void initCloseSideRoutines();
            void initFarSideRoutines();
            void initSkillsRoutines();

            // State
            int selectedRoutine = 0;

        private:
            char limitSwitchPort;
            std::vector<Routine> routines;
            std::vector<std::string> routineNames;
    };
}

#endif // __AUTON_LIB