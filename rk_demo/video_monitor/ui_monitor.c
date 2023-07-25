#include "home_ui.h"
#include "ui_intercom_homepage.h"

#include <time.h>

lv_obj_t *ui_Screen_monitor;

lv_obj_t *ui_monitor_Label_0;
lv_obj_t *ui_monitor_Label_1;

lv_obj_t *ui_circular_0;
lv_obj_t *ui_circular_1;
lv_obj_t *ui_circular_2;
lv_obj_t *ui_circular_3;
lv_obj_t *ui_circular_mid;


static lv_obj_t *ui_back;
static lv_obj_t *ui_pause;
static lv_obj_t *ui_webcam;
static lv_obj_t *ui_forward;
static lv_obj_t *ui_backward;
static lv_obj_t *ui_video_background;
static lv_obj_t *bg_pic;

extern lv_style_t style_txt_s;
extern lv_style_t style_txt_m;

extern lv_img_dsc_t ui_img_pause;
extern lv_img_dsc_t ui_img_webcam;
extern lv_img_dsc_t ui_img_forward;
extern lv_img_dsc_t ui_img_backward;
extern lv_img_dsc_t ui_img_circular;
extern lv_img_dsc_t ui_img_video_background;


static void back_icon_cb(lv_event_t *e)
{
    lv_event_code_t code = lv_event_get_code(e);
    lv_obj_t *obj = lv_event_get_target(e);
    if (code == LV_EVENT_CLICKED)
    {
        intercom_homepage_ui_init();
        lv_obj_del(ui_Screen_monitor);
        ui_Screen_monitor = NULL;
    }
}

void ui_monitor_screen_init()
{
    ui_Screen_monitor = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_Screen_monitor, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_set_style_bg_img_opa(ui_Screen_monitor, 0, LV_PART_MAIN | LV_STATE_DEFAULT);
    lv_obj_add_style(ui_Screen_monitor, &style_txt_s, LV_PART_MAIN);

    bg_pic = lv_img_create(ui_Screen_monitor);
    lv_obj_set_pos(bg_pic, 0, 0);
    lv_img_set_src(bg_pic, BG_PIC_0);

    //video_background
    ui_video_background = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_video_background, &ui_img_video_background);
    lv_obj_set_width(ui_video_background, LV_SIZE_CONTENT);
    lv_obj_set_height(ui_video_background, LV_SIZE_CONTENT);
    lv_img_set_zoom(ui_video_background, 160);
    lv_obj_set_x(ui_video_background, -140);
    lv_obj_set_y(ui_video_background, 400);
    //lv_obj_align_to(ui_video_background, ui_back, LV_ALIGN_OUT_BOTTOM_LEFT, 0, 0);
    lv_obj_add_flag(ui_video_background, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_video_background, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    //back img
    ui_back = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_back, IMG_RETURN_BTN);
    lv_obj_set_width(ui_back, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_back, LV_SIZE_CONTENT);    /// 32
    lv_obj_align(ui_back, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_flag(ui_back, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_back, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_event_cb(ui_back, back_icon_cb, LV_EVENT_ALL, 0);

    /*text:Video Monitor*/
    ui_monitor_Label_0 = lv_label_create(ui_Screen_monitor);
    lv_label_set_text(ui_monitor_Label_0, "视频监控");
    lv_obj_set_style_text_color(ui_monitor_Label_0, lv_color_white(), LV_PART_MAIN);
    lv_obj_add_style(ui_monitor_Label_0, &style_txt_m, LV_PART_MAIN);
    lv_obj_align_to(ui_monitor_Label_0, ui_back,
                    LV_ALIGN_OUT_RIGHT_MID,
                    5, 0);

    //circular_left
    ui_circular_0 = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_circular_0, &ui_img_circular);
    lv_obj_set_size(ui_circular_0, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_circular_0, ui_video_background, LV_ALIGN_OUT_RIGHT_MID, -160, 60);
    ui_backward = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_backward, &ui_img_backward);
    lv_obj_set_size(ui_backward, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_backward, ui_circular_0, LV_ALIGN_CENTER, 0, -3);


    //circular_right
    ui_circular_1 = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_circular_1, &ui_img_circular);
    lv_obj_set_size(ui_circular_1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_circular_1, ui_video_background, LV_ALIGN_OUT_RIGHT_MID, 5, 60);
    ui_forward = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_forward, &ui_img_forward);
    lv_obj_set_size(ui_forward, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_forward, ui_circular_1, LV_ALIGN_CENTER, 0, -3);


    ui_circular_mid = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_circular_mid, &ui_img_circular);
    lv_img_set_zoom(ui_circular_mid, 400);
    lv_obj_set_size(ui_circular_mid, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_circular_mid, ui_video_background, LV_ALIGN_OUT_RIGHT_MID, -75, 60);
    ui_monitor_Label_1 = lv_label_create(ui_Screen_monitor);
    lv_obj_set_size(ui_monitor_Label_1, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_monitor_Label_1, ui_circular_mid, LV_ALIGN_CENTER, -3, -5);
    lv_label_set_text(ui_monitor_Label_1, "主机1");

    ////webcam
    ui_circular_2 = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_circular_2, &ui_img_circular);
    lv_obj_set_size(ui_circular_2, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_circular_2, ui_circular_mid, LV_ALIGN_OUT_TOP_MID, 0, 0);
    ui_webcam = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_webcam, &ui_img_webcam);
    lv_obj_set_size(ui_webcam, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_webcam, ui_circular_2, LV_ALIGN_CENTER, 0, -3);


    //pause
    ui_circular_3 = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_circular_3, &ui_img_circular);
    lv_obj_set_size(ui_circular_3, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_circular_3, ui_circular_mid, LV_ALIGN_OUT_BOTTOM_MID, 0, 0);
    ui_pause = lv_img_create(ui_Screen_monitor);
    lv_img_set_src(ui_pause, &ui_img_pause);
    lv_obj_set_size(ui_pause, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
    lv_obj_align_to(ui_pause, ui_circular_3, LV_ALIGN_CENTER, 0, -3);

}

void monitor_ui_init()
{
    if (!ui_Screen_monitor)
        ui_monitor_screen_init();
    lv_disp_load_scr(ui_Screen_monitor);
}