#include "autonlib.hpp"
#include "display/lv_core/lv_obj.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_btnm.h"
#include "display/lv_objx/lv_img.h"
#include "display/lv_objx/lv_tabview.h"
#include "displaylib/display.hpp"
#include "main.h"

LV_IMG_DECLARE(img_match);
LV_IMG_DECLARE(img_skills);

autonlib::AutonManager::AutonManager(char limitSwitchPort)
    : limitSwitchPort(limitSwitchPort) 
{}


void autonlib::AutonManager::addRoutine(Routine routine) {
    this->routines.push_back(routine);
    this->routineNames.push_back(routine.routineName);
}


void autonlib::AutonManager::smartStartInit() {
    
    // Reset Subsystem Sensors
    subsystems::chassis.resetIMUs();
	subsystems::kicker.resetRotationSensor();

    // Init Routines
    initCloseSideRoutines();
    initFarSideRoutines();
    initSkillsRoutines();

    // ** STARTUP SEQUENCE FOR DISPLAY

    // Logo & Background
    displaylib::setBackgroundColor(LV_COLOR_BLACK);
    displaylib::displayLogo();

    // Progress Bar & Text
    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label, "Initializing...");
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -30);

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain); // Initialize with the default style
    style.text.color = LV_COLOR_WHITE;
    lv_obj_set_style(label, &style);

	displaylib::animateSliderFor(2000);
	pros::delay(2000);

    // Wait until calibarations are finished
    int errTimer = 0;
	while (subsystems::chassis.IMUFront.is_calibrating() && subsystems::chassis.IMUBack.is_calibrating()) {
        if(errTimer == 10000) {
            lv_label_set_text(label, "Calibration Failed! Please Check \nPorts & Conduct Manual Resets.");
            lv_obj_align(label, NULL, LV_ALIGN_CENTER, 0, -30);
            displaylib::setBackgroundColor(LV_COLOR_RED);
        }
        pros::delay(10);
        errTimer+=10;
    }

    lv_label_set_text(label, "Done!");
    pros::delay(400);
    

    // Clear screen after finished
    lv_obj_clean(lv_scr_act());
} 

/*Called when a button is released ot long pressed*/
static lv_res_t btnm_action(lv_obj_t * btnm, const char *txt)
{
    printf("Button: %s released\n", txt);

    return LV_RES_OK; /*Return OK because the button matrix is not deleted*/
}

void autonlib::AutonManager::displaySelector() {
    
    /*Create a Tab view object*/
    lv_obj_t *tabview;
    tabview = lv_tabview_create(lv_scr_act(), NULL);

    /*Add 3 tabs (the tabs are page (lv_page) and can be scrolled*/
    lv_obj_t *closeSideTab = lv_tabview_add_tab(tabview, "Close Side");
    lv_obj_t *farSideTab = lv_tabview_add_tab(tabview, "Far Side");

    /* TABVIEW STYLES */
        static lv_style_t tabviewBgStyle;
        lv_style_copy(&tabviewBgStyle, &lv_style_plain); 
        tabviewBgStyle.body.main_color = LV_COLOR_BLACK;
        tabviewBgStyle.body.grad_color = LV_COLOR_BLACK;
        tabviewBgStyle.body.padding.inner = 0;
        tabviewBgStyle.text.color = LV_COLOR_WHITE;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BG, &tabviewBgStyle);

        static lv_style_t tabviewIndicStyle;
        lv_style_copy(&tabviewIndicStyle, &lv_style_plain); 
        tabviewIndicStyle.body.main_color = LV_COLOR_WHITE; 
        tabviewIndicStyle.body.grad_color = LV_COLOR_WHITE;
        tabviewIndicStyle.body.empty = true;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_INDIC, &tabviewIndicStyle);

        static lv_style_t tabviewBtnPressedStyle;
        lv_style_copy(&tabviewBtnPressedStyle, &lv_style_plain); 
        tabviewBtnPressedStyle.body.main_color = LV_COLOR_WHITE; 
        tabviewBtnPressedStyle.body.grad_color = LV_COLOR_WHITE;
        tabviewBtnPressedStyle.text.color = LV_COLOR_BLACK;
        tabviewBtnPressedStyle.body.padding.ver = 8;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_PR, &tabviewBtnPressedStyle);

        static lv_style_t tabviewBtnReleasedStyle;
        lv_style_copy(&tabviewBtnReleasedStyle, &lv_style_plain); 
        tabviewBtnReleasedStyle.body.main_color = LV_COLOR_BLACK; 
        tabviewBtnReleasedStyle.body.grad_color = LV_COLOR_BLACK;
        tabviewBtnReleasedStyle.text.color = LV_COLOR_WHITE;
        tabviewBtnReleasedStyle.body.padding.ver = 8;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_REL, &tabviewBtnReleasedStyle);

        static lv_style_t tabviewBtnTglPressedStyle;
        lv_style_copy(&tabviewBtnTglPressedStyle, &lv_style_plain); 
        tabviewBtnTglPressedStyle.body.main_color = LV_COLOR_WHITE; 
        tabviewBtnTglPressedStyle.body.grad_color = LV_COLOR_WHITE;
        tabviewBtnTglPressedStyle.text.color = LV_COLOR_BLACK;
        tabviewBtnTglPressedStyle.body.padding.ver = 8;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_TGL_PR, &tabviewBtnTglPressedStyle);

        static lv_style_t tabviewBtnTglReleasedStyle;
        lv_style_copy(&tabviewBtnTglReleasedStyle, &lv_style_plain); 
        tabviewBtnTglReleasedStyle.body.main_color = LV_COLOR_WHITE; 
        tabviewBtnTglReleasedStyle.body.grad_color = LV_COLOR_WHITE;
        tabviewBtnTglReleasedStyle.text.color = LV_COLOR_BLACK;
        tabviewBtnTglReleasedStyle.body.padding.ver = 8;
        lv_tabview_set_style(tabview, LV_TABVIEW_STYLE_BTN_TGL_REL, &tabviewBtnTglReleasedStyle);

    /* TAB CONTENT */

    /* CLOSE SIDE */
    lv_obj_t *closeSideField = lv_img_create(closeSideTab, NULL);
	lv_img_set_src(closeSideField, &img_match);
	lv_obj_align(closeSideField, NULL, LV_ALIGN_CENTER, -150, -10);
    static const char * closeSideBtnMatrix_map[] = {"Rush 6 Ball", "2", "3", "\n", "4", "5", "6", ""};


    /* FAR SIDE */
    lv_obj_t *farSideField = lv_img_create(farSideTab, NULL);
	lv_img_set_src(farSideField, &img_match);
	lv_obj_align(farSideField, NULL, LV_ALIGN_CENTER, -150, -10);
    static const char * farSideBtnMatrix_map[] = {"1", "2", "3", "\n", "4", "5", "6", ""};

    

    /* CREATE ROUTINE MAPS */
    std::vector<std::string> closeSideRoutineNames = {};
    std::vector<std::string> farSideRoutineNames = {};

    for(Routine routine : routines) {
        if(routine.routineType == CLOSE_SIDE) closeSideRoutineNames.push_back(routine.routineName);
        else if (routine.routineType == FAR_SIDE) farSideRoutineNames.push_back(routine.routineName);
    }

    // Create Button Matrix Maps
    // static const char * closeSideBtnMatrix_map[] = {closeSideRoutineNames[0].c_str(), closeSideRoutineNames[1].c_str(), closeSideRoutineNames[2].c_str(), "\n", closeSideRoutineNames[3].c_str(), closeSideRoutineNames[4].c_str(), closeSideRoutineNames[5].c_str(), ""};
    // static const char * farSideBtnMatrix_map[] = {closeSideRoutineNames[0].c_str(), closeSideRoutineNames[1].c_str(), closeSideRoutineNames[2].c_str(), "\n", closeSideRoutineNames[3].c_str(), closeSideRoutineNames[4].c_str(), closeSideRoutineNames[5].c_str(), ""};


    /*Create a default button matrix*/
    lv_obj_t * btnm1 = lv_btnm_create(closeSideTab, NULL);
    lv_btnm_set_map(btnm1, closeSideBtnMatrix_map);
    lv_btnm_set_action(btnm1, btnm_action);
    lv_obj_set_size(btnm1, LV_HOR_RES-210, LV_VER_RES / 3);
    lv_obj_align(btnm1, closeSideTab, LV_ALIGN_CENTER, 90, -40);

    /*Create a new style for the button matrix back ground*/
    static lv_style_t style_bg;
    lv_style_copy(&style_bg, &lv_style_plain);
    style_bg.body.main_color = LV_COLOR_SILVER;
    style_bg.body.grad_color = LV_COLOR_SILVER;
    // style_bg.text
    style_bg.body.padding.hor = 0;
    style_bg.body.padding.ver = 0;
    style_bg.body.padding.inner = 0;

    lv_btnm_set_style(btnm1, LV_BTNM_STYLE_BG, &style_bg);

}