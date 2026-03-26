/**
 * @file lv_port_disp.c
 *
 */

#include <stdlib.h>
#include <lvgl/lvgl.h>
#include <lvgl/src/drivers/display/drm/lv_linux_drm.h>
#include <lvgl/src/drivers/display/rkadk/rkadk.h>
#include <lvgl/src/drivers/sdl/lv_sdl_window.h>

void lv_port_disp_init(lv_coord_t hor_res, lv_coord_t ver_res, int rot)
{
    lv_display_rotation_t lvgl_rot = LV_DISPLAY_ROTATION_0;
    lv_display_t *disp;

    switch (rot)
    {
    case 0:
        lvgl_rot = LV_DISPLAY_ROTATION_0;
        break;
    case 90:
        lvgl_rot = LV_DISPLAY_ROTATION_90;
        break;
    case 180:
        lvgl_rot = LV_DISPLAY_ROTATION_180;
        break;
    case 270:
        lvgl_rot = LV_DISPLAY_ROTATION_270;
        break;
    default:
        LV_LOG_ERROR("Unsupported rotation %d", rot);
        break;
    }

#if defined(LV_USE_LINUX_DRM) && LV_USE_LINUX_DRM
    LV_LOG_USER("LV_USE_LINUX_DRM");
#if defined(LV_DRM_USE_EGL) && LV_DRM_USE_EGL
    const char *device = "/dev/dri/card0";
    disp = lv_linux_drm_create();
    lv_linux_drm_set_file(disp, device, -1);
#else
    disp = lv_drm_disp_create(hor_res, ver_res, rot);
#endif
#endif

#if defined(LV_USE_SDL) && LV_USE_SDL
    LV_LOG_USER("LV_USE_SDL");
    disp = lv_sdl_window_create(hor_res, ver_res);
#endif
}

void lv_port_disp_deinit(void)
{
#if defined(LV_USE_LINUX_DRM) && LV_USE_LINUX_DRM
#if defined(LV_DRM_USE_EGL) && LV_DRM_USE_EGL
    LV_LOG_WARN("lv_linux_drm_destroy has no implement");
#else
    lv_display_t *disp = lv_display_get_default();
    lv_drm_disp_delete(disp);
#endif
#endif

#if defined(LV_USE_SDL) && LV_USE_SDL
    lv_sdl_quit();
#endif
}

