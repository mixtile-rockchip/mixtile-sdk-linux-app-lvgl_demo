#if USE_DRM
#include "lvgl/lvgl.h"
#include "lvgl/lv_conf.h"
#include "lv_drivers/display/drm.h"

void hal_drm_init(lv_coord_t hor_res, lv_coord_t ver_res)
{
  drm_init();

  /*Create a display*/
  static lv_disp_drv_t disp_drv;
  drm_disp_drv_init(&disp_drv);

  lv_disp_t * disp = lv_disp_drv_register(&disp_drv);
}
#endif

