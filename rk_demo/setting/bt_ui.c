#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <time.h>
#include <unistd.h>

#include <lvgl/lvgl.h>

#include "main.h"
#include "cJSON.h"
#include "ui_resource.h"

static int init_done = 0;

static lv_obj_t * bg;
static lv_obj_t * item_scan;
static lv_obj_t * item_scan_icon;

static lv_obj_t * part_switch;
static lv_obj_t * part_saved;
static lv_obj_t * part_scaned;

static lv_obj_t * bt_label;
static lv_obj_t * bt_switch;

static lv_obj_t * item_label_saved;
static lv_obj_t * item_label_scaned;

static lv_obj_t * item_list_saved;
static lv_obj_t * item_list_scaned;

static lv_timer_t * timer;

static lv_anim_t icon_anim;

static lv_style_t style_txt;
static lv_style_t style_list;

static volatile bool rkbt_gonff = false;
static int bt_result = 0;

static void lv_saved_bt_list(lv_obj_t * parent);

int bt_connected(void)
{
    return 0;
}

static void read_saved_bt(int check)
{
}

static void style_init(void)
{
    lv_style_init(&style_txt);
    lv_style_set_text_font(&style_txt, ttf_main_s.font);
    lv_style_set_text_color(&style_txt, lv_color_make(0xff, 0x23, 0x23));

    lv_style_init(&style_list);
    lv_style_set_text_font(&style_list, ttf_main_m.font);
    lv_style_set_text_color(&style_list, lv_color_black());
}

static void icon_anim_end(lv_anim_t *anim)
{
    if (!init_done)
        return;

    lv_obj_clear_flag(item_scan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_add_flag(item_scan_icon, LV_OBJ_FLAG_HIDDEN);
}

static void icon_anim_cb(void * var, int32_t v)
{
    lv_img_set_angle(var, v);
}

static void scan_btn_cb(lv_event_t * e)
{
    lv_obj_add_flag(item_scan, LV_OBJ_FLAG_HIDDEN);
    lv_obj_clear_flag(item_scan_icon, LV_OBJ_FLAG_HIDDEN);
    lv_anim_start(&icon_anim);
}

static void label_drawed_cb(lv_event_t * e)
{
    if (!item_scan)
        return;

    lv_obj_align_to(item_scan, lv_event_get_target(e),
                    LV_ALIGN_OUT_TOP_RIGHT, 0, 0);
}

static void bt_update(lv_timer_t * timer)
{
    if (bt_result)
    {
        lv_anim_del(&icon_anim, NULL);
        bt_result = 0;
    }
}

static void switch_toggled(lv_event_t * e)
{
    lv_obj_t * sw = lv_event_get_target(e);

    if (lv_obj_has_state(sw, LV_STATE_CHECKED))
    {
        lv_obj_clear_flag(item_label_saved,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(part_saved,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(item_label_scaned,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(part_scaned,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_clear_flag(item_scan,
                          LV_OBJ_FLAG_HIDDEN);
    }
    else
    {
        lv_obj_add_flag(item_label_saved,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(part_saved,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(item_label_scaned,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(part_scaned,
                          LV_OBJ_FLAG_HIDDEN);
        lv_obj_add_flag(item_scan,
                          LV_OBJ_FLAG_HIDDEN);
    }
}

lv_obj_t * menu_bt_init(lv_obj_t * parent)
{
    style_init();

    bg = lv_obj_create(parent);
    lv_obj_remove_style_all(bg);
    lv_obj_set_size(bg, lv_pct(100), lv_pct(100));
    lv_obj_set_flex_flow(bg, LV_FLEX_FLOW_COLUMN);
    lv_obj_center(bg);

    part_switch = lv_obj_create(bg);
    lv_obj_set_width(part_switch, lv_pct(100));
    lv_obj_set_height(part_switch, LV_SIZE_CONTENT);
    lv_obj_add_style(part_switch, &style_txt, LV_PART_MAIN);

    bt_label = lv_label_create(part_switch);
    lv_obj_align(bt_label, LV_ALIGN_LEFT_MID, 0, 0);
    lv_label_set_text(bt_label, "BT");
    lv_obj_add_style(bt_label, &style_txt, LV_PART_MAIN);
    bt_switch = lv_switch_create(part_switch);
    lv_obj_align(bt_switch, LV_ALIGN_RIGHT_MID, 0, 0);
    lv_obj_add_state(bt_switch, LV_STATE_CHECKED);
    lv_obj_add_event_cb(bt_switch, switch_toggled, LV_EVENT_VALUE_CHANGED, NULL);

    item_label_saved = lv_label_create(bg);
    lv_label_set_text(item_label_saved, "已保存设备");
    lv_obj_add_style(item_label_saved, &style_txt, LV_PART_MAIN);

    part_saved = lv_obj_create(bg);
    lv_obj_remove_style_all(part_saved);
    lv_obj_set_width(part_saved, lv_pct(100));
    lv_obj_set_height(part_saved, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(part_saved, LV_FLEX_FLOW_COLUMN);

    item_label_scaned = lv_label_create(bg);
    lv_label_set_text(item_label_scaned, "可用设备");
    lv_obj_add_style(item_label_scaned, &style_txt, LV_PART_MAIN);

    part_scaned = lv_obj_create(bg);
    lv_obj_remove_style_all(part_scaned);
    lv_obj_set_width(part_scaned, lv_pct(100));
    lv_obj_set_height(part_scaned, LV_SIZE_CONTENT);
    lv_obj_set_flex_flow(part_scaned, LV_FLEX_FLOW_COLUMN);

    lv_obj_add_event_cb(part_scaned, label_drawed_cb, LV_EVENT_DRAW_POST_END, NULL);

    item_list_saved = lv_list_create(part_saved);
    lv_obj_set_size(item_list_saved, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_add_style(item_list_saved, &style_list, LV_PART_MAIN);
    lv_list_add_btn(item_list_saved, NULL, "无");

    item_list_scaned = lv_list_create(part_scaned);
    lv_obj_set_size(item_list_scaned, lv_pct(100), LV_SIZE_CONTENT);
    lv_obj_add_style(item_list_scaned, &style_list, LV_PART_MAIN);
    lv_list_add_btn(item_list_scaned, NULL, "无");

    read_saved_bt(1);

    item_scan = lv_label_create(bg);
    lv_label_set_text(item_scan, "刷新");
    lv_obj_add_style(item_scan, &style_txt, LV_PART_MAIN);
    lv_obj_align_to(item_scan, part_scaned, LV_ALIGN_OUT_TOP_RIGHT, 0, 0);
    lv_obj_add_event_cb(item_scan, scan_btn_cb, LV_EVENT_CLICKED, NULL);
    lv_obj_add_flag(item_scan, LV_OBJ_FLAG_CLICKABLE | LV_OBJ_FLAG_IGNORE_LAYOUT);

    item_scan_icon = lv_img_create(bg);
    lv_img_set_src(item_scan_icon, WIFI_SCANNING);
    lv_img_set_angle(item_scan_icon, 0);
    lv_obj_align_to(item_scan_icon, item_scan, LV_ALIGN_CENTER, 0, 0);
    lv_obj_add_flag(item_scan_icon, LV_OBJ_FLAG_HIDDEN | LV_OBJ_FLAG_IGNORE_LAYOUT);

    lv_anim_init(&icon_anim);
    lv_anim_set_var(&icon_anim, item_scan_icon);
    lv_anim_set_values(&icon_anim, 0, 3600);
    lv_anim_set_time(&icon_anim, 1000);
    lv_anim_set_exec_cb(&icon_anim, icon_anim_cb);
    lv_anim_set_path_cb(&icon_anim, lv_anim_path_linear);
    lv_anim_set_deleted_cb(&icon_anim, icon_anim_end);
    lv_anim_set_repeat_count(&icon_anim, 3/*LV_ANIM_REPEAT_INFINITE*/);
    scan_btn_cb(NULL);

    timer = lv_timer_create(bt_update, 1000, NULL);
    lv_timer_enable(timer);

    init_done = 1;

    return bg;
}

void menu_bt_deinit(void)
{
    init_done = 0;
    lv_timer_del(timer);
    lv_anim_set_deleted_cb(&icon_anim, NULL);
    lv_anim_set_exec_cb(&icon_anim, NULL);
    lv_anim_del(&icon_anim, NULL);
    lv_obj_del(bg);
    bg = NULL;
}

