#include <stdio.h>
#include <lvgl/lvgl.h>

#include "furniture_control_ui.h"
#include "home_ui.h"
#include "icebox_ui.h"

///////////////////// VARIABLES ////////////////////
extern uint32_t LV_EVENT_GET_COMP_CHILD;

static lv_obj_t * furniture_control_ui_Screen1 = NULL;
static lv_obj_t * furniture_control_ui_return;
static lv_obj_t * furniture_control_ui_Label2;
static lv_obj_t * furniture_control_ui_icebox;
static lv_obj_t * furniture_control_ui_player;
static lv_obj_t * furniture_control_ui_coffee_machine;
static lv_obj_t * furniture_control_ui_Label1;
static lv_obj_t * furniture_control_ui_Label4;
static lv_obj_t * furniture_control_ui_Label3;
///////////////////// TEST LVGL SETTINGS ////////////////////

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
void furniture_control_page_jump_home_callback(lv_event_t* event) {
    printf("page_jump_return_home_callback is into \n");
    home_ui_init();
    lv_obj_del(furniture_control_ui_Screen1);
    furniture_control_ui_Screen1 = NULL;
}

void furniture_control_page_jump_icebox_callback(lv_event_t* event) {
    printf("furniture_control_page_jump_icebox_callback is into \n");
    icebox_ui_init();
    lv_obj_del(furniture_control_ui_Screen1);
    furniture_control_ui_Screen1 = NULL;
}

///////////////////// SCREENS ////////////////////

void ui_furniture_control_screen_init(void)
{
    furniture_control_ui_Screen1 = lv_obj_create(NULL);
    lv_obj_clear_flag(furniture_control_ui_Screen1, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    furniture_control_ui_return = lv_img_create(furniture_control_ui_Screen1);
    lv_img_set_src(furniture_control_ui_return, IMG_RETURN_BTN);
    //lv_img_set_src(furniture_control_ui_return, &ui_img_return_png);
    lv_obj_set_width(furniture_control_ui_return, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(furniture_control_ui_return, LV_SIZE_CONTENT);    /// 32
    lv_obj_set_x(furniture_control_ui_return, -352);
    lv_obj_set_y(furniture_control_ui_return, -189);
    lv_obj_set_align(furniture_control_ui_return, LV_ALIGN_CENTER);
    lv_obj_add_flag(furniture_control_ui_return, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(furniture_control_ui_return, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(furniture_control_ui_return, LV_OBJ_FLAG_CLICKABLE);
    if (furniture_control_ui_return != NULL) {
        lv_obj_add_event_cb(furniture_control_ui_return, furniture_control_page_jump_home_callback, LV_EVENT_CLICKED, NULL);
    }

    furniture_control_ui_Label2 = lv_label_create(furniture_control_ui_Screen1);
    lv_obj_set_width(furniture_control_ui_Label2, 249);
    lv_obj_set_height(furniture_control_ui_Label2, 26);
    lv_obj_set_x(furniture_control_ui_Label2, -135);
    lv_obj_set_y(furniture_control_ui_Label2, -184);
    lv_obj_set_align(furniture_control_ui_Label2, LV_ALIGN_CENTER);
    lv_label_set_text(furniture_control_ui_Label2, "furniture control");


    furniture_control_ui_icebox = lv_img_create(furniture_control_ui_Screen1);
    lv_img_set_src(furniture_control_ui_icebox, IMG_ICEBOX);
    lv_obj_set_width(furniture_control_ui_icebox, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(furniture_control_ui_icebox, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_x(furniture_control_ui_icebox, -241);
    lv_obj_set_y(furniture_control_ui_icebox, -40);
    lv_obj_set_align(furniture_control_ui_icebox, LV_ALIGN_CENTER);
    lv_obj_add_flag(furniture_control_ui_icebox, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(furniture_control_ui_icebox, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(furniture_control_ui_icebox, LV_OBJ_FLAG_CLICKABLE);
    if (furniture_control_ui_icebox != NULL) {
        printf("icebox callback\n");
        lv_obj_add_event_cb(furniture_control_ui_icebox, furniture_control_page_jump_icebox_callback, LV_EVENT_CLICKED, NULL);
    }

    furniture_control_ui_player = lv_img_create(furniture_control_ui_Screen1);
    lv_img_set_src(furniture_control_ui_player, IMG_PLAYER);
    lv_obj_set_width(furniture_control_ui_player, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(furniture_control_ui_player, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_x(furniture_control_ui_player, -1);
    lv_obj_set_y(furniture_control_ui_player, -40);
    lv_obj_set_align(furniture_control_ui_player, LV_ALIGN_CENTER);
    lv_obj_add_flag(furniture_control_ui_player, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(furniture_control_ui_player, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(furniture_control_ui_player, LV_OBJ_FLAG_CLICKABLE);


    furniture_control_ui_coffee_machine = lv_img_create(furniture_control_ui_Screen1);
    lv_img_set_src(furniture_control_ui_coffee_machine, IMG_COFFEE);
    lv_obj_set_width(furniture_control_ui_coffee_machine, LV_SIZE_CONTENT);   /// 64
    lv_obj_set_height(furniture_control_ui_coffee_machine, LV_SIZE_CONTENT);    /// 64
    lv_obj_set_x(furniture_control_ui_coffee_machine, 248);
    lv_obj_set_y(furniture_control_ui_coffee_machine, -40);
    lv_obj_set_align(furniture_control_ui_coffee_machine, LV_ALIGN_CENTER);
    lv_obj_add_flag(furniture_control_ui_coffee_machine, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(furniture_control_ui_coffee_machine, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(furniture_control_ui_coffee_machine, LV_OBJ_FLAG_CLICKABLE);

    furniture_control_ui_Label1 = lv_label_create(furniture_control_ui_Screen1);
    lv_obj_set_width(furniture_control_ui_Label1, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(furniture_control_ui_Label1, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(furniture_control_ui_Label1, -240);
    lv_obj_set_y(furniture_control_ui_Label1, 20);
    lv_obj_set_align(furniture_control_ui_Label1, LV_ALIGN_CENTER);
    lv_label_set_text(furniture_control_ui_Label1, "Icebox");

    furniture_control_ui_Label4 = lv_label_create(furniture_control_ui_Screen1);
    lv_obj_set_width(furniture_control_ui_Label4, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(furniture_control_ui_Label4, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(furniture_control_ui_Label4, 5);
    lv_obj_set_y(furniture_control_ui_Label4, 20);
    lv_obj_set_align(furniture_control_ui_Label4, LV_ALIGN_CENTER);
    lv_label_set_text(furniture_control_ui_Label4, "Promotional video");

    furniture_control_ui_Label3 = lv_label_create(furniture_control_ui_Screen1);
    lv_obj_set_width(furniture_control_ui_Label3, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(furniture_control_ui_Label3, LV_SIZE_CONTENT);    /// 1
    lv_obj_set_x(furniture_control_ui_Label3, 244);
    lv_obj_set_y(furniture_control_ui_Label3, 20);
    lv_obj_set_align(furniture_control_ui_Label3, LV_ALIGN_CENTER);
    lv_label_set_text(furniture_control_ui_Label3, "Coffee machine");
}

void furniture_control_ui_init(void)
{
    if (!furniture_control_ui_Screen1)
        ui_furniture_control_screen_init();
    lv_disp_load_scr(furniture_control_ui_Screen1);
}

