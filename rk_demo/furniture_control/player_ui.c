#define MAX_FILE_COUNT 10
#define PATH_VIDEO "/oem/"
#include <stdio.h>
#include <stdlib.h>
#include <dirent.h>
#include "main.h"
#include "player_ui.h"
#include "furniture_control_ui.h"

///////////////////// VARIABLES ////////////////////
static lv_obj_t *ui_player_screen = NULL;
static lv_obj_t *player_label;
static lv_obj_t *ui_return;
static lv_obj_t *player_box = NULL;
static lv_obj_t *player_box_canvas = NULL;
static lv_obj_t *player_box_button = NULL;
static lv_obj_t *player_start_button = NULL;
static lv_obj_t *player_stop_button = NULL;
static lv_obj_t *player_list_button = NULL;
static lv_obj_t *video_label = NULL;
static lv_obj_t *video_list_box = NULL;
static lv_obj_t *video_list = NULL;
static lv_obj_t *bg_pic = NULL;


static lv_style_t style_txt;
static lv_style_t style_list;
//static lv_img_dsc_t * bg_snapshot;
///////////////////// TEST LVGL SETTINGS ////////////////////

///////////////////// ANIMATIONS ////////////////////

///////////////////// FUNCTIONS ////////////////////
// static void bg_pic_snapshot_blur(void)
// {
//     lv_draw_rect_dsc_t dsc;

//     bg_snapshot = lv_snapshot_take(bg_pic, LV_IMG_CF_TRUE_COLOR);

//     lv_obj_t * canvas = lv_canvas_create(NULL);
//     lv_area_t area;
//     lv_canvas_set_buffer(canvas, bg_snapshot->data,
//                          bg_snapshot->header.w,
//                          bg_snapshot->header.h,
//                          bg_snapshot->header.cf);
//     area.x1 = 0;
//     area.y1 = 0;
//     area.x2 = bg_snapshot->header.w - 1;
//     area.y2 = bg_snapshot->header.h - 1;
//     lv_canvas_blur_ver(canvas, &area, 100);
//     lv_canvas_blur_hor(canvas, &area, 100);
//     lv_draw_rect_dsc_init(&dsc);
//     dsc.bg_opa = 70;
//     dsc.bg_color = lv_color_black();
//     lv_canvas_draw_rect(canvas, 0, 0,
//                         bg_snapshot->header.w,
//                         bg_snapshot->header.h, &dsc);
//     lv_obj_del(canvas);
// }

static void style_init(void)
{
    lv_style_init(&style_txt);
    lv_style_set_text_font(&style_txt, ttf_main_s.font);
    lv_style_set_text_color(&style_txt, lv_color_make(0xff, 0x23, 0x23));

    lv_style_init(&style_list);
    lv_style_set_text_font(&style_list, ttf_main_m.font);
    lv_style_set_text_color(&style_list, lv_color_black());
}

void player_page_jump_furniture_control_callback(lv_event_t *event)
{
    printf("player_page_jump_furniture_control_callback is into \n");
    furniture_control_ui_init();
    lv_obj_del(ui_player_screen);
    //free(bg_snapshot);
    ui_player_screen = NULL;
    video_list_box = NULL;
}

void video_name_callback(lv_event_t *event)
{
    char *file_name = lv_event_get_user_data(event);
    printf("video_name select file %s\n", file_name);
    lv_label_set_text(video_label, file_name);
    lv_obj_del(video_list_box);
    video_list_box = NULL;
}

void player_list_button_callback(lv_event_t *event)
{
    printf("player_list_button_callback is into \n");
    DIR *dir;
    struct dirent *entry;
    int file_count = 0;
    if (video_list_box == NULL)
    {
        video_list_box = lv_obj_create(player_box);
        //lv_obj_remove_style_all(video_list_box);
        lv_obj_set_width(video_list_box, lv_pct(50));
        lv_obj_set_height(video_list_box, lv_pct(40));
        lv_obj_align(video_list_box, LV_ALIGN_TOP_LEFT, 0, lv_pct(40));

        video_list = lv_list_create(video_list_box);
        lv_obj_set_size(video_list, lv_pct(100), lv_pct(100));
        lv_obj_center(video_list);
        lv_obj_add_style(video_list, &style_list, LV_PART_MAIN);
        lv_obj_set_style_pad_column(video_list, 10, LV_PART_MAIN);

        dir = opendir(PATH_VIDEO);
        if (dir == NULL)
        {
            printf("Error opening directory /oem\n");
            return;
        }
        while ((entry = readdir(dir)) != NULL)
        {
            if (entry->d_type == DT_REG)
            {
                //add_file_to_list(entry->d_name);
                lv_obj_t *obj_text = lv_list_add_btn(video_list, NULL, entry->d_name);
                lv_obj_add_flag(obj_text, LV_OBJ_FLAG_CLICKABLE);
                lv_obj_add_event_cb(obj_text, video_name_callback, LV_EVENT_CLICKED, entry->d_name);
                file_count++;
                if (file_count >= MAX_FILE_COUNT)
                {
                    break;
                }
            }
        }
    }
    else
    {
        lv_obj_del(video_list_box);
        video_list_box = NULL;
    }
}
///////////////////// SCREENS ////////////////////
void ui_player_screen_init(void)
{
    style_init();

    ui_player_screen = lv_obj_create(NULL);
    lv_obj_clear_flag(ui_player_screen, LV_OBJ_FLAG_SCROLLABLE);      /// Flags

    bg_pic = lv_img_create(ui_player_screen);
    lv_obj_set_pos(bg_pic, 0, 0);
    lv_img_set_src(bg_pic, BG_PIC_1);
    //bg_pic_snapshot_blur();

    ui_return = lv_img_create(ui_player_screen);
    lv_img_set_src(ui_return, IMG_RETURN_BTN);
    lv_obj_set_width(ui_return, LV_SIZE_CONTENT);   /// 32
    lv_obj_set_height(ui_return, LV_SIZE_CONTENT);    /// 32
    lv_obj_align(ui_return, LV_ALIGN_TOP_LEFT, 10, 10);
    lv_obj_add_flag(ui_return, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(ui_return, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    if (ui_return != NULL)
    {
        lv_obj_add_event_cb(ui_return, player_page_jump_furniture_control_callback, LV_EVENT_CLICKED, NULL);
    }

    player_label = lv_label_create(ui_player_screen);
    lv_obj_set_width(player_label, 249);
    lv_obj_set_height(player_label, 26);
    lv_obj_align(player_label, LV_ALIGN_TOP_LEFT, 100, 20);
    lv_obj_add_style(player_label, &style_txt_m, LV_PART_MAIN);
    lv_label_set_text(player_label, "宣传视频");

    player_box = lv_obj_create(ui_player_screen);
    lv_obj_remove_style_all(player_box);
    lv_obj_set_width(player_box, lv_pct(100));
    lv_obj_set_height(player_box, lv_pct(80));
    lv_obj_align(player_box, LV_ALIGN_TOP_LEFT, 0, lv_pct(10));

    player_box_canvas = lv_obj_create(player_box);
    lv_obj_remove_style_all(player_box_canvas);
    lv_obj_set_width(player_box_canvas, lv_pct(100));
    lv_obj_set_height(player_box_canvas, lv_pct(70));

    player_box_button = lv_obj_create(player_box);
    lv_obj_remove_style_all(player_box_button);
    lv_obj_set_width(player_box_button, lv_pct(100));
    lv_obj_set_height(player_box_button, lv_pct(30));
    lv_obj_align(player_box_button, LV_ALIGN_TOP_LEFT, 0, lv_pct(70));

    player_start_button = lv_img_create(player_box_button);
    lv_img_set_src(player_start_button, IMG_PLAYER_START);
    lv_obj_set_width(player_start_button, 128);   /// 64
    lv_obj_set_height(player_start_button, 128);    /// 64
    lv_obj_set_align(player_start_button, LV_ALIGN_CENTER);
    lv_obj_add_flag(player_start_button, LV_OBJ_FLAG_CLICKABLE);

    player_stop_button = lv_img_create(player_box_button);
    lv_img_set_src(player_stop_button, IMG_PLAYER_STOP);
    lv_obj_set_width(player_stop_button, 128);   /// 64
    lv_obj_set_height(player_stop_button, 128);    /// 64
    lv_obj_align(player_stop_button, LV_ALIGN_CENTER, 250, 0);
    lv_obj_add_flag(player_stop_button, LV_OBJ_FLAG_CLICKABLE);

    player_list_button = lv_img_create(player_box_button);
    lv_img_set_src(player_list_button, IMG_PLAYER_LIST);
    lv_obj_set_width(player_list_button, 128);   /// 64
    lv_obj_set_height(player_list_button, 128);    /// 64
    lv_obj_align(player_list_button, LV_ALIGN_CENTER, -250, 0);
    lv_obj_add_flag(player_list_button, LV_OBJ_FLAG_ADV_HITTEST);     /// Flags
    lv_obj_clear_flag(player_list_button, LV_OBJ_FLAG_SCROLLABLE);      /// Flags
    lv_obj_add_flag(player_list_button, LV_OBJ_FLAG_CLICKABLE);
    if (player_list_button != NULL)
    {
        lv_obj_add_event_cb(player_list_button, player_list_button_callback, LV_EVENT_CLICKED, NULL);
    }

    video_label = lv_label_create(player_box_button);
    lv_obj_set_width(video_label, LV_SIZE_CONTENT);   /// 1
    lv_obj_set_height(video_label, LV_SIZE_CONTENT);    /// 1
    lv_obj_align(video_label, LV_ALIGN_CENTER, 0, 100);
    lv_obj_add_style(video_label, &style_txt_m, LV_PART_MAIN);
    lv_label_set_text(video_label, "");

}

void player_ui_init(void)
{
    if (!ui_player_screen)
        ui_player_screen_init();
    lv_disp_load_scr(ui_player_screen);
}
