/*******************************************************************************
 * Size: 14 px
 * Bpp: 2
 * Opts: 
 ******************************************************************************/

#ifdef LV_LVGL_H_INCLUDE_SIMPLE
#include "lvgl.h"
#else
#include "lvgl/lvgl.h"
#endif

#ifndef TEST_1
#define TEST_1 1
#endif

#if TEST_1



/*Store the image of the glyphs*/
static LV_ATTRIBUTE_LARGE_CONST const uint8_t glyph_bitmap[] = {
    /* U+63A7 "控" */
    0x9, 0x0, 0x40, 0x0, 0x80, 0x6, 0x0, 0x8,
    0x15, 0x66, 0x85, 0xea, 0x10, 0x24, 0x8, 0x17,
    0xa, 0x0, 0x80, 0x80, 0x34, 0xa, 0x20, 0x1,
    0x87, 0xc1, 0x55, 0xb0, 0x8, 0x0, 0xc0, 0x0,
    0x80, 0xc, 0x0, 0x8, 0x0, 0xc0, 0x0, 0xc0,
    0xc, 0x10, 0x2c, 0x15, 0x96, 0x40, 0x0, 0x0,
    0x0,

    /* U+76D1 "监" */
    0x0, 0x20, 0x80, 0x0, 0x83, 0xc, 0x0, 0xc,
    0x31, 0x95, 0xc0, 0xc3, 0x20, 0x0, 0xc, 0x32,
    0x20, 0x0, 0xc3, 0x40, 0xc0, 0x8, 0x30, 0x8,
    0x0, 0x40, 0x0, 0x10, 0xd, 0x75, 0xd7, 0x0,
    0xc3, 0xc, 0x30, 0xc, 0x30, 0xc3, 0x0, 0xc3,
    0xc, 0x34, 0x19, 0x65, 0x96, 0x80,

    /* U+89C6 "视" */
    0x4, 0x0, 0x0, 0x0, 0x30, 0xd5, 0x5c, 0x1,
    0xc, 0x0, 0x81, 0x5d, 0xc3, 0x8, 0x0, 0x8c,
    0x30, 0x80, 0x20, 0xc3, 0x8, 0x7, 0xc, 0x20,
    0x80, 0xb9, 0xc6, 0x8, 0x13, 0x1c, 0x68, 0x80,
    0x30, 0xd, 0x80, 0x3, 0x1, 0x98, 0x0, 0x30,
    0x21, 0x81, 0x2, 0x14, 0xf, 0xe0, 0x0, 0x0,
    0x0,

    /* U+9891 "频" */
    0x0, 0x40, 0x0, 0x0, 0x12, 0x5, 0xa6, 0x40,
    0xce, 0x82, 0x0, 0x3, 0x20, 0x48, 0x10, 0xc,
    0x86, 0x55, 0xc0, 0x55, 0x5c, 0x23, 0x0, 0x8,
    0x21, 0x8c, 0x3, 0x66, 0xc6, 0x30, 0x24, 0xa6,
    0x14, 0xc0, 0x42, 0xc8, 0x82, 0x0, 0x8, 0x2,
    0x50, 0x0, 0x90, 0x20, 0x70, 0x14, 0x5, 0x0,
    0x80, 0x0, 0x0, 0x0, 0x0
};


/*---------------------
 *  GLYPH DESCRIPTION
 *--------------------*/

static const lv_font_fmt_txt_glyph_dsc_t glyph_dsc[] = {
    {.bitmap_index = 0, .adv_w = 0, .box_w = 0, .box_h = 0, .ofs_x = 0, .ofs_y = 0} /* id = 0 reserved */,
    {.bitmap_index = 0, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 49, .adv_w = 224, .box_w = 14, .box_h = 13, .ofs_x = 0, .ofs_y = -1},
    {.bitmap_index = 95, .adv_w = 224, .box_w = 14, .box_h = 14, .ofs_x = 0, .ofs_y = -2},
    {.bitmap_index = 144, .adv_w = 224, .box_w = 15, .box_h = 14, .ofs_x = 0, .ofs_y = -2}
};

/*---------------------
 *  CHARACTER MAPPING
 *--------------------*/

static const uint16_t unicode_list_0[] = {
    0x0, 0x132a, 0x261f, 0x34ea
};

/*Collect the unicode lists and glyph_id offsets*/
static const lv_font_fmt_txt_cmap_t cmaps[] =
{
    {
        .range_start = 25511, .range_length = 13547, .glyph_id_start = 1,
        .unicode_list = unicode_list_0, .glyph_id_ofs_list = NULL, .list_length = 4, .type = LV_FONT_FMT_TXT_CMAP_SPARSE_TINY
    }
};



/*--------------------
 *  ALL CUSTOM DATA
 *--------------------*/

#if LV_VERSION_CHECK(8, 0, 0)
/*Store all the custom data of the font*/
static  lv_font_fmt_txt_glyph_cache_t cache;
static const lv_font_fmt_txt_dsc_t font_dsc = {
#else
static lv_font_fmt_txt_dsc_t font_dsc = {
#endif
    .glyph_bitmap = glyph_bitmap,
    .glyph_dsc = glyph_dsc,
    .cmaps = cmaps,
    .kern_dsc = NULL,
    .kern_scale = 0,
    .cmap_num = 1,
    .bpp = 2,
    .kern_classes = 0,
    .bitmap_format = 0,
#if LV_VERSION_CHECK(8, 0, 0)
    .cache = &cache
#endif
};


/*-----------------
 *  PUBLIC FONT
 *----------------*/

/*Initialize a public general font descriptor*/
#if LV_VERSION_CHECK(8, 0, 0)
const lv_font_t Video_monitor = {
#else
lv_font_t Video_monitor = {
#endif
    .get_glyph_dsc = lv_font_get_glyph_dsc_fmt_txt,    /*Function pointer to get glyph's data*/
    .get_glyph_bitmap = lv_font_get_bitmap_fmt_txt,    /*Function pointer to get glyph's bitmap*/
    .line_height = 14,          /*The maximum line height required by the font*/
    .base_line = 2,             /*Baseline measured from the bottom of the line*/
#if !(LVGL_VERSION_MAJOR == 6 && LVGL_VERSION_MINOR == 0)
    .subpx = LV_FONT_SUBPX_NONE,
#endif
#if LV_VERSION_CHECK(7, 4, 0) || LVGL_VERSION_MAJOR >= 8
    .underline_position = -2,
    .underline_thickness = 1,
#endif
    .dsc = &font_dsc           /*The custom font data. Will be accessed by `get_glyph_bitmap/dsc` */
};


#endif /*#if TEST_1*/

