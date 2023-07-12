#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

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
static lv_timer_t * timer_date;

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////

void home_page_jump_furniture_control_callback(lv_event_t* event) {
    printf("page_jump_furniture_control_callback is into \n");
    furniture_control_ui_init();
    lv_timer_del(timer_date);
    lv_obj_del(ui_Screen1);
    ui_Screen1 = NULL;
}

// static int go_ping(char *svrip) {  //103.235.46.40
//     int time=0;
//     pid_t pid;
//     if ((pid = vfork()) < 0) {
//         printf("\nvfork error\n");
//         return 0;
//     }else if (pid == 0) {       
//         if ( execlp("ping", "ping","-c","1",svrip, (char*)0) < 0) {
//             printf("\nexeclp error\n");
//             return 0;
//         }
//     }
//     int stat;
//     waitpid(pid, &stat, 0);
//     if (stat == 0) {
//         printf("ping ok\n");
//         return 0;
//     }else {
//         printf("ping error\n");
//         return -1;  
//     }
// }

static void date_update(lv_timer_t * timer)
{
    time_t time_ptr;
    struct tm * tim;

    time(&time_ptr);
    tim = localtime(&time_ptr);
    //printf("update time %04d-%02d-%02d %02d:%02d \n", tim->tm_year + 1900, tim->tm_mon + 1, tim->tm_mday, tim->tm_hour, tim->tm_min);
    lv_label_set_text_fmt(ui_Label_time, "%04d-%02d-%02d %02d:%02d", tim->tm_year + 1900, tim->tm_mon + 1, tim->tm_mday, tim->tm_hour, tim->tm_min);
}

///////////////////// SCREENS ////////////////////
void ui_Screen1_screen_init(void)
{
    ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_opa(ui_Screen1, 0, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_wifi = lv_img_create(ui_Screen1);
    lv_img_set_src(ui_wifi, IMG_WIFI_OFF);
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
    lv_obj_set_style_bg_img_src(ui_smart_home, IMG_SMART_HOME, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_set_style_bg_img_src(ui_furniture_control, IMG_FURNITURE, LV_PART_MAIN | LV_STATE_DEFAULT);
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
    lv_obj_set_style_bg_img_src(ui_phone, IMG_PHONE, LV_PART_MAIN | LV_STATE_DEFAULT);

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
    lv_obj_set_style_bg_img_src(ui_setting, IMG_SETTING, LV_PART_MAIN | LV_STATE_DEFAULT);

    ui_Label_time = lv_label_create(ui_Screen1);
    lv_obj_set_width(ui_Label_time, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(ui_Label_time, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(ui_Label_time, 230);
    lv_obj_set_y(ui_Label_time, -210);
    lv_obj_set_align(ui_Label_time, LV_ALIGN_CENTER);
    date_update(NULL);
    timer_date = lv_timer_create(date_update, 1000, NULL);
    lv_timer_enable(timer_date);

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
    lv_img_set_src(ui_logo, IMG_RK_LOGO);
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
