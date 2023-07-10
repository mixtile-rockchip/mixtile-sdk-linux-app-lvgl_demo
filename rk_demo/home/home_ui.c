#include <stdio.h>
#include <lvgl/lvgl.h>

#include "furniture_control_ui.h"
#include "home_ui.h"

///////////////////// VARIABLES ////////////////////
uint32_t LV_EVENT_GET_COMP_CHILD;

static lv_obj_t * ui_Screen1 = NULL;
static lv_obj_t * ui_wifi;
static lv_obj_t * ui_smart_home;
static lv_obj_t * ui_furniture_control;
static lv_obj_t * ui_phone;
static lv_obj_t * ui_setting;
static lv_obj_t * ui_Label_time;
static lv_obj_t * ui_Label1;
static lv_obj_t * ui_Label4;
static lv_obj_t * ui_Label3;
static lv_obj_t * ui_Label6;
static lv_obj_t * ui_logo;

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void home_page_jump_furniture_control_callback(lv_event_t* event) {
    printf("page_jump_furniture_control_callback is into \n");
    furniture_control_ui_init();
    lv_obj_del(ui_Screen1);
    ui_Screen1 = NULL;
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_opa(ui_Screen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_wifi, &ui_img_wifi);
    lv_obj_set_width(ui_wifi, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(ui_wifi, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_x(ui_wifi, 367);
    lv_obj_set_y(ui_wifi, -213);
    lv_obj_set_align(ui_wifi, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_wifi, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_wifi, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_wifi, 120);

    //Smart home page
    ui_smart_home = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_smart_home, 130);
    lv_obj_set_height(ui_smart_home, 130);
    lv_obj_set_x(ui_smart_home, -261);
    lv_obj_set_y(ui_smart_home, -20);
    lv_obj_set_align(ui_smart_home, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_smart_home, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_smart_home, lv_color_hex(0xDED6D6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_smart_home, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_smart_home, &ui_img_home_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    //furniture_control
    ui_furniture_control = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_furniture_control, 130);
    lv_obj_set_height(ui_furniture_control, 130);
    lv_obj_set_x(ui_furniture_control, -80);
    lv_obj_set_y(ui_furniture_control, -20);
    lv_obj_set_align(ui_furniture_control, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_furniture_control, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_furniture_control, lv_color_hex(0xDED6D6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_furniture_control, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_furniture_control, &ui_img_trello_png, LV_PART_MAIN | LV_STATE_DEFAULT);
    if (ui_furniture_control != NULL) {
        lv_obj_add_event_cb(ui_furniture_control, home_page_jump_furniture_control_callback, LV_EVENT_CLICKED, NULL);
    }

    //phone page
    ui_phone = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_phone, 130);
    lv_obj_set_height(ui_phone, 130);
    lv_obj_set_x(ui_phone, 97);
    lv_obj_set_y(ui_phone, -20);
    lv_obj_set_align(ui_phone, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_phone, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_phone, lv_color_hex(0xDED6D6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_phone, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_phone, &ui_img_phone_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    //setting page
    ui_setting = lv_obj_create(ui_Screen1);
    lv_obj_set_width(ui_setting, 130);
    lv_obj_set_height(ui_setting, 130);
    lv_obj_set_x(ui_setting, 268);
    lv_obj_set_y(ui_setting, -20);
    lv_obj_set_align(ui_setting, LV_ALIGN_CENTER);
    lv_obj_clear_flag(ui_setting, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_color(ui_setting, lv_color_hex(0xDED6D6), LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_opa(ui_setting, 255, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_set_style_bg_img_src(ui_setting, &ui_img_setting_png, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_time = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label_time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_time, 230);
    lv_obj_set_y(ui_Label_time, -210);
    lv_obj_set_align(ui_Label_time, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label_time, "2023-06-20  16:33");

    ui_Label1 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label1, -262);
    lv_obj_set_y(ui_Label1, 79);
    lv_obj_set_align(ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label1, "Smart home");

    ui_Label4 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label4, -78);
    lv_obj_set_y(ui_Label4, 79);
    lv_obj_set_align(ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label4, "Furniture control");

    ui_Label3 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label3, 99);
    lv_obj_set_y(ui_Label3, 79);
    lv_obj_set_align(ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label3, "intercom");

    ui_Label6 = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label6, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label6, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label6, 270);
    lv_obj_set_y(ui_Label6, 79);
    lv_obj_set_align(ui_Label6, LV_ALIGN_CENTER);
    lv_label_set_text(ui_Label6, "Settings");

    ui_logo = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_logo, &ui_img_logo_png);
    lv_obj_set_width(ui_logo, LV_SIZE_CONTENT);   /// 186
    lv_obj_set_height(ui_logo, LV_SIZE_CONTENT);    /// 90
    lv_obj_set_x(ui_logo, -323);
    lv_obj_set_y(ui_logo, -207);
    lv_obj_set_align(ui_logo, LV_ALIGN_CENTER);
    lv_obj_add_flag(ui_logo, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_logo, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_img_set_zoom(ui_logo, 150);

}

void home_ui_init(void)
{
    if (!ui_Screen1)
        ui_Screen1_screen_init();
    lv_disp_load_scr(ui_Screen1);
}

void rk_demo_init(void)
{
    LV_EVENT_GET_COMP_CHILD = lv_event_register_id();

    lv_disp_t * dispp = lv_disp_get_default();
    lv_theme_t * theme = lv_theme_default_init(dispp, lv_palette_main(LV_PALETTE_BLUE), lv_palette_main(LV_PALETTE_RED),
                                               false, LV_FONT_DEFAULT);
    lv_disp_set_theme(dispp, theme);

    home_ui_init();
}
