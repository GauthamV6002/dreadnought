#include "displaylib/display.hpp"
#include "display/lv_conf.h"
#include "display/lv_conf_checker.h"
#include "display/lv_core/lv_obj.h"
#include "display/lv_core/lv_style.h"
#include "display/lv_fonts/lv_font_builtin.h"
#include "display/lv_misc/lv_color.h"
#include "display/lv_objx/lv_bar.h"
#include "display/lv_objx/lv_label.h"
#include "main.h"

// Images
LV_IMG_DECLARE(angel_logo_50);
LV_IMG_DECLARE(match);
LV_IMG_DECLARE(skills);

void displaylib::displayLogo() {
    lv_obj_t *img = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img, &angel_logo_50);
	lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain); // Initialize with the default style
    style.image.opa = LV_OPA_20; // Set opacity
    lv_obj_set_style(img, &style);
}

void displaylib::displayMatchField() {
    lv_obj_t *img = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img, &match);
	lv_obj_align(img, NULL, LV_ALIGN_CENTER, -130, 0);
}

void displaylib::displaySkillsField() {
    lv_obj_t *img = lv_img_create(lv_scr_act(), NULL);
	lv_img_set_src(img, &skills);
	lv_obj_align(img, NULL, LV_ALIGN_CENTER, 0, 0);
}