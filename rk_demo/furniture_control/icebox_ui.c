#include <stdio.h>
#include "main.h"
#include "icebox_ui.h"
#include "furniture_control_ui.h"

///////////////////// VARIABLES ////////////////////
static lv_obj_t * ui_icebox_screen;
static lv_obj_t * ui_icebox_tem;
static lv_obj_t * ui_Label1;
static lv_obj_t * ui_Label2;
static lv_obj_t * ui_Label3;
static lv_obj_t * ui_rice;
static lv_obj_t * ui_return;

///////////////////// TEST LVGL SETTINGS ////////////////////

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void icebox_page_jump_furniture_control_callback(lv_event_t* event) {
    printf("icebox_page_jump_furniture_control_callback is into \n");
    furniture_control_ui_init();
    lv_obj_del(ui_icebox_screen);
    ui_icebox_screen = NULL;
}

///////////////////// SCREENS ////////////////////
void ui_icebox_screen_init(void)
{
    ui_icebox_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_icebox_screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_icebox_screen);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -131);
    lv_obj_set_y(ui_Label1, -104);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_obj_add_style(ui_Label1, &style_txt_m, LV_PART_MAIN);
    lv_label_set_text(ui_Label1, "每日食谱-炒饭");

    ui_Label2 = lv_label_create(ui_icebox_screen);
    lv_obj_set_width(ui_Label2, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label2, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label2, -146);
    lv_obj_set_y(ui_Label2, -72);
    lv_obj_set_align(ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label2, "");

    ui_Label3 = lv_label_create(ui_icebox_screen);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, -53);
    lv_obj_set_y(ui_Label3, 1);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_obj_add_style(ui_Label3, &style_txt_m, LV_PART_MAIN);
    lv_label_set_text(ui_Label3,
                      "将火腿粒、玉米粒、青豆、胡萝卜入锅一起炒匀，\n加适量的盐调味、滴几滴蚝油炒匀。");

    ui_rice = lv_img_create(ui_icebox_screen);
    lv_img_set_src(ui_rice, IMG_RICE);
    lv_obj_set_width(ui_rice, LV_SIZE_CONTENT);   /// 150
    lv_obj_set_height(ui_rice, LV_SIZE_CONTENT);    /// 115
    lv_obj_set_x(ui_rice, 330);
    lv_obj_set_y(ui_rice, 1);
    lv_obj_set_align(ui_rice, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_rice, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_rice, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_return = lv_img_create(ui_icebox_screen);
    lv_img_set_src(ui_return, IMG_RETURN_BTN);
    lv_obj_set_width(ui_return, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_return, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(ui_return, -346);
    lv_obj_set_y(ui_return, -180);
    lv_obj_set_align(ui_return, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_return, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_return, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    if (ui_return != NULL) {
        lv_obj_add_event_cb(ui_return, icebox_page_jump_furniture_control_callback, LV_EVENT_CLICKED, NULL);
    }

}

void icebox_ui_init(void)
{
    if (!ui_icebox_screen)
        ui_icebox_screen_init();
    lv_disp_load_scr(ui_icebox_screen);
}
