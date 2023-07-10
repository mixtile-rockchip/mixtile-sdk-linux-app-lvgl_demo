#ifdef __cplusplus
extern "C" {
#endif

#include "lvgl/lvgl.h"

LV_IMG_DECLARE(ui_img_wifi);    // assets\wifi (1).png
LV_IMG_DECLARE(ui_img_home_png);    // assets\home.png
LV_IMG_DECLARE(ui_img_trello_png);    // assets\trello.png
LV_IMG_DECLARE(ui_img_phone_png);    // assets\phone.png
LV_IMG_DECLARE(ui_img_setting_png);    // assets\sliders.png
LV_IMG_DECLARE(ui_img_logo_png);    // assets\logo.png

void rk_demo_init(void);
void home_ui_init(void);

#ifdef __cplusplus
} /*extern "C"*/
#endif
