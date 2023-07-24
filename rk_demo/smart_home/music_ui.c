#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include "bt.h"
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
static lv_obj_t * label_pos;
static lv_obj_t * label_time;
static lv_obj_t * btn_play;
static lv_obj_t * label_bt_state;
static lv_timer_t * timer;
static lv_timer_t * pos_timer;

static char * btn_img[] = {
    LV_SYMBOL_PREV,
    LV_SYMBOL_PLAY,
    LV_SYMBOL_NEXT,
    LV_SYMBOL_VOLUME_MID,
    LV_SYMBOL_VOLUME_MAX,
    LV_SYMBOL_MUTE,
};

static int bt_sink_enabled = 0;
static int volume = 100;
static int mute = 0;
static int g_pos = 0;

static void btn_cb(lv_event_t * e)
{
    intptr_t idx = (intptr_t)lv_event_get_user_data(e);

    if (bt_sink_state() == RK_BT_SINK_STATE_IDLE ||
        bt_sink_state() == RK_BT_SINK_STATE_DISCONNECT)
        return;

    switch (idx)
    {
    case 0:
        bt_sink_prev();
        break;
    case 1:
        if (bt_sink_is_started())
            bt_sink_pause();
        else
            bt_sink_play();
        break;
    case 2:
        bt_sink_next();
        break;
    case 3:
        if (volume >= 10)
            volume -= 10;
        bt_sink_set_volume(volume);
        break;
    case 4:
        if (volume <= 90)
            volume += 10;
        bt_sink_set_volume(volume);
        break;
    case 5:
        if (mute)
            bt_sink_set_volume(volume);
        else
            bt_sink_set_volume(0);
        mute = !mute;
        break;
    }
}

static void pos_timer_cb(struct _lv_timer_t *tmr)
{
    static int sink_started = -1;
    int pos, time;

    if (sink_started != bt_sink_is_started())
    {
        sink_started = bt_sink_is_started();
        if (sink_started)
            lv_label_set_text(btn_play, LV_SYMBOL_PAUSE);
        else
            lv_label_set_text(btn_play, LV_SYMBOL_PLAY);
    }

    if (bt_sink_get_track_time(&pos, &time))
    {
        g_pos = pos;
        lv_slider_set_range(slider, 0, time);
        lv_slider_set_value(slider, pos, LV_ANIM_ON);
        time /= 1000;
        lv_label_set_text_fmt(label_time, "%02d:%02d", time / 60, time % 60);
    }
    else
    {
        if (!sink_started)
            return;
        g_pos += 100;
        lv_slider_set_value(slider, g_pos, LV_ANIM_ON);
    }
    pos = g_pos / 1000;
    lv_label_set_text_fmt(label_pos, "%02d:%02d", pos / 60, pos % 60);
}

static void bt_timer_cb(struct _lv_timer_t *tmr)
{
    char *title, *artist;
    int vol;

    if ((bt_sink_enabled == 0)
        && bt_is_state_on())
    {
        bt_sink_enabled = 1;
        bt_sink_enable();
        lv_label_set_text(label_bt_state,
                          "蓝牙：已开启 A2DP：等待连接");
    }

    if (bt_sink_enabled)
    {
        if (bt_sink_state() != RK_BT_SINK_STATE_IDLE &&
            bt_sink_state() != RK_BT_SINK_STATE_DISCONNECT)
            lv_label_set_text(label_bt_state,
                              "蓝牙：已开启 A2DP：已连接");
    }

    if (bt_sink_get_track_info(&title, &artist))
    {
        lv_label_set_text(label_singer,
                          artist ? artist : "未知歌手");
        lv_label_set_text(label_song,
                          title ? title : "未知歌曲");
        if (artist)
            free(artist);
        if (title)
            free(title);
    }

    if (bt_sink_get_vol(&vol))
    {
        volume = vol;
    }
}

lv_obj_t * menu_music_init(lv_obj_t * parent)
{
    lv_obj_t * obj;
    int x, y;
    int ofs;

    if (bt_is_state_on())
    {
        bt_sink_enable();
        bt_sink_enabled = 1;
    }
    else
    {
        bt_sink_enabled = 0;
    }

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

    label_bt_state = lv_label_create(bg);
    if (bt_sink_enabled)
        lv_label_set_text(label_bt_state,
                          "蓝牙：已开启 A2DP：等待连接");
    else
        lv_label_set_text(label_bt_state,
                          "蓝牙：未开启");
    lv_obj_add_style(label_bt_state, &style_txt_s, LV_PART_MAIN);
    lv_obj_set_style_text_color(label_bt_state, lv_color_white(), LV_PART_MAIN);
    lv_obj_align(label_bt_state, LV_ALIGN_TOP_RIGHT, 0, 0);

    area_player = lv_obj_create(bg);
    lv_obj_remove_style_all(area_player);
    lv_obj_set_size(area_player, lv_pct(80), lv_pct(85));
    lv_obj_align(area_player, LV_ALIGN_BOTTOM_MID, 0, 0);
    lv_obj_set_style_pad_left(area_player, 10, LV_PART_MAIN);
    lv_obj_set_style_pad_right(area_player, 10, LV_PART_MAIN);
    lv_obj_clear_flag(area_player, LV_OBJ_FLAG_SCROLLABLE);

    area_label = lv_obj_create(area_player);
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
    lv_slider_set_range(slider, 0, 10000);
    lv_slider_set_value(slider, 0, LV_ANIM_OFF);
    lv_obj_align(slider, LV_ALIGN_CENTER, 0, 0);

    label_pos = lv_label_create(area_player);
    lv_obj_align(label_pos, LV_ALIGN_LEFT_MID, 0, -20);
    lv_label_set_text(label_pos, "00:00");
    lv_obj_set_style_text_color(label_pos, lv_color_white(), LV_PART_MAIN);

    label_time = lv_label_create(area_player);
    lv_obj_align(label_time, LV_ALIGN_RIGHT_MID, 0, -20);
    lv_label_set_text(label_time, "00:00");
    lv_obj_set_style_text_color(label_time, lv_color_white(), LV_PART_MAIN);

    area_btn = lv_obj_create(area_player);
    lv_obj_remove_style_all(area_btn);
    lv_obj_set_size(area_btn, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_align_to(area_btn, slider, LV_ALIGN_OUT_BOTTOM_MID, 0, 20);
    lv_obj_set_style_pad_column(area_btn, 30, LV_PART_MAIN);
    lv_obj_set_flex_align(area_btn, LV_FLEX_ALIGN_CENTER,
                          LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

    for (intptr_t i = 0; i < 6; i++)
    {
        obj = lv_btn_create(area_btn);
        lv_obj_add_event_cb(obj, btn_cb, LV_EVENT_CLICKED, (void *)i);
        obj = lv_label_create(obj);
        lv_label_set_text(obj, btn_img[i]);
        if (i == 1)
            btn_play = obj;
    }

    timer = lv_timer_create(bt_timer_cb, 100, NULL);
    pos_timer = lv_timer_create(pos_timer_cb, 100, NULL);

    return bg;
}

void menu_music_deinit(void)
{
    lv_obj_del(bg);
    bg = NULL;

    free(bg_img);
    lv_timer_del(timer);
    lv_timer_del(pos_timer);

    if (bt_sink_enabled)
    {
        if (bt_sink_state() != RK_BT_SINK_STATE_IDLE &&
            bt_sink_state() != RK_BT_SINK_STATE_DISCONNECT)
        {
            bt_sink_pause();
            bt_sink_disconnect();
        }
        bt_sink_disable();
        bt_sink_enabled = 0;
    }
}

