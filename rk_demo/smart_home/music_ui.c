#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include "main.h"
#include "ui_resource.h"
#include "smart_home_ui.h"

static lv_obj_t * bg;

static lv_img_dsc_t * bg_snapshot;

static lv_img_dsc_t * bg_img;

static lv_obj_t * area_player;
static lv_obj_t * area_label;
static lv_obj_t * slider;
static lv_obj_t * area_btn;
static lv_obj_t * box_btn;
static lv_obj_t * label_singer;
static lv_obj_t * label_song;
static char * btn_img[] = {
    IMG_SKIP_BACK,
    IMG_PLAY,
    IMG_SKIP_FORWARD,
    IMG_VOL_DOWN,
    IMG_VOL_UP,
    IMG_VOL_MUTE,
};

lv_obj_t * menu_music_init(lv_obj_t * parent)
{
    lv_obj_t * obj;
    int x, y;
    int ofs;

    bg = lv_img_create(parent);
    lv_obj_remove_style_all(bg);
    lv_obj_set_size(bg, lv_pct(90), lv_pct(30));
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_SCROLLABLE);
    lv_obj_clear_flag(bg, LV_OBJ_FLAG_ADV_HITTEST);
    lv_obj_center(bg);
    lv_obj_refr_size(bg);
    lv_obj_refr_pos(bg);

    bg_snapshot = smart_home_ui_bg_blur();
    bg_img = malloc(sizeof(*bg_img));
    memcpy(bg_img, bg_snapshot, sizeof(*bg_img));

    x = lv_obj_get_x(bg);
    y = lv_obj_get_y(bg);
    ofs = (y * bg_img->header.w + x)
          * lv_img_cf_get_px_size(bg_img->header.cf) / 8;
    bg_img->data = bg_snapshot->data + ofs;
    lv_img_set_src(bg, bg_img);

    obj = lv_label_create(bg);
    lv_label_set_text(obj, "蓝牙音乐");
    lv_obj_add_style(obj, &style_txt_s, LV_PART_MAIN);
    lv_obj_set_style_text_color(obj, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(obj, LV_ALIGN_TOP_LEFT, 0, 0);

    area_player = lv_obj_create(bg);
    lv_obj_remove_style_all(area_player);
    lv_obj_set_size(area_player, lv_pct(80), lv_pct(90));
    lv_obj_align(area_player, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_pad_left(area_player, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_right(area_player, 10, LV_PART_MAIN);
    lv_obj_clear_flag(area_player, LV_OBJ_FLAG_SCROLLABLE);

    area_label = lv_slider_create(area_player);
    lv_obj_remove_style_all(area_label);
    lv_obj_set_size(area_label, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(area_label, LV_FLEX_FLOW_COLUMN);
    lv_obj_set_style_pad_row(area_label, 10, 0);
    lv_obj_align(area_label, LV_ALIGN_OUT_TOP_LEFT, 0, 0);

    label_singer = lv_label_create(area_label);
    lv_label_set_text(label_singer, "歌曲名");
    lv_obj_add_style(label_singer, &style_txt_m, LV_PART_MAIN);
    lv_obj_set_style_text_color(label_singer, lv_color_white(), LV_PART_MAIN);

    label_song = lv_label_create(area_label);
    lv_label_set_text(label_song, "歌手名");
    lv_obj_add_style(label_song, &style_txt_m, LV_PART_MAIN);
    lv_obj_set_style_text_color(label_song, lv_color_white(), LV_PART_MAIN);

    slider = lv_slider_create(area_player);
    lv_obj_set_width(slider, lv_pct(100));
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);

    area_btn = lv_obj_create(area_player);
    lv_obj_remove_style_all(area_btn);
    lv_obj_set_size(area_btn, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_align_to(area_btn, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_obj_set_style_pad_column(area_btn, 30, LV_PART_MAIN);
    lv_obj_set_flex_align(area_btn, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for (int i = 0; i < 6; i++)
    {
        obj = lv_img_create(area_btn);
        lv_img_set_src(obj, btn_img[i]);
    }

    return bg;
}

void menu_music_deinit(void)
{
    lv_obj_del(bg);
    bg = NULL;

    free(bg_img);
}

