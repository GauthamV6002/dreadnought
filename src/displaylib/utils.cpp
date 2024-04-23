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

void displaylib::setBackgroundColor(lv_color32_t color) {
    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain); // Initialize with the default style
    style.body.main_color = color; // Set the main color
    style.body.grad_color = color; // Set the gradient color (if needed)
    style.body.opa = LV_OPA_COVER; // Set opacity

    // Set the background style for the screen
    lv_obj_set_style(lv_scr_act(), &style);
}

void displaylib::showCenterText(std::string text, int xOffset, int yOffset) {

    lv_obj_t *label = lv_label_create(lv_scr_act(), NULL);
	lv_label_set_text(label, text.c_str());
    lv_obj_align(label, NULL, LV_ALIGN_CENTER, xOffset, yOffset);

    static lv_style_t style;
    lv_style_copy(&style, &lv_style_plain); // Initialize with the default style
    style.text.color = LV_COLOR_WHITE;
    lv_obj_set_style(label, &style);
} 

void displaylib::animateSliderFor(int millis) {
    
    lv_obj_t *slider = lv_bar_create(lv_scr_act(), NULL);
    lv_obj_set_size(slider, lv_obj_get_width(lv_scr_act()) / 2, LV_DPI / 4);
    lv_obj_align(slider, lv_scr_act(), LV_ALIGN_CENTER, 0, 20);

    /*Create a style*/
    static lv_style_t style_indic;
    lv_style_copy(&style_indic, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
    style_indic.body.main_color = LV_COLOR_WHITE;
    style_indic.body.grad_color = LV_COLOR_WHITE;
    style_indic.body.border.color = LV_COLOR_WHITE;

    style_indic.body.radius = 0;
    style_indic.body.padding.inner = 0;
    style_indic.body.padding.hor = 0;
    style_indic.body.padding.ver = 0;

    lv_bar_set_style(slider, LV_BAR_STYLE_BG, &style_indic); 


    static lv_style_t style_bg;
    lv_style_copy(&style_bg, &lv_style_plain);    /*Copy a built-in style to initialize the new style*/
    style_indic.body.main_color = LV_COLOR_BLACK;
    style_indic.body.grad_color = LV_COLOR_BLACK;
    style_indic.body.border.color = LV_COLOR_BLACK;
    style_indic.body.border.width = 2;
    style_indic.body.radius = 0;
    style_indic.body.padding.inner = 1;
    lv_bar_set_style(slider, LV_BAR_STYLE_INDIC, &style_bg); 

    lv_bar_set_value_anim(slider, 100, millis);
}