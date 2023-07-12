#include <stdio.h>
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
#if LV_COLOR_DEPTH != 32
    #error "LV_COLOR_DEPTH should be 32bit to match SquareLine Studio's settings"
#endif
#if LV_COLOR_16_SWAP !=0
    #error "LV_COLOR_16_SWAP should be 0 to match SquareLine Studio's settings"
#endif

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

    ui_icebox_tem = lv_img_create(ui_icebox_screen);
    lv_img_set_src(ui_icebox_tem, &ui_img_icebox_tem_png);
    lv_obj_set_width(ui_icebox_tem, LV_SIZE_CONTENT);   /// 128
    lv_obj_set_height(ui_icebox_tem, LV_SIZE_CONTENT);    /// 128
    lv_obj_set_x(ui_icebox_tem, -254);
    lv_obj_set_y(ui_icebox_tem, -3);
    lv_obj_set_align(ui_icebox_tem, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_icebox_tem, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_icebox_tem, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_Label1 = lv_label_create(ui_icebox_screen);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -131);
    lv_obj_set_y(ui_Label1, -104);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
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
    lv_label_set_text(ui_Label3,
                      "准备米饭一大碗，滴几滴香油，拌匀。\n准备好胡萝卜、青豆、玉米粒。\n将胡萝卜粒、玉米粒、青豆焯熟待用。\n火腿肠切粒。\n起油锅，将火腿粒煎炒一下。\n将火腿粒盛起待用。\n鸡蛋两只搅拌均匀。\n将火腿粒、玉米粒、青豆、胡萝卜入锅一起炒匀，\n加适量的盐调味、滴几滴蚝油炒匀就行了。");

    ui_rice = lv_img_create(ui_icebox_screen);
    lv_img_set_src(ui_rice, &ui_img_rice_png);
    lv_obj_set_width(ui_rice, LV_SIZE_CONTENT);   /// 150
    lv_obj_set_height(ui_rice, LV_SIZE_CONTENT);    /// 115
    lv_obj_set_x(ui_rice, 191);
    lv_obj_set_y(ui_rice, 1);
    lv_obj_set_align(ui_rice, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_rice, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_rice, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    ui_return = lv_img_create(ui_icebox_screen);
    lv_img_set_src(ui_return, &ui_img_return_png);
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
