#ifndef __BT_H__
#define __BT_H__

#include <RkBtSink.h>

bool bt_sink_is_started(void);
bool bt_is_state_on(void);
RK_BT_SINK_STATE bt_sink_state(void);
int bt_ble_init(void);
int bt_ble_deinit(void);
int bt_sink_enable(void);
int bt_sink_disable(void);
int bt_sink_disconnect(void);
int bt_sink_set_volume(int volume);
int bt_sink_next(void);
int bt_sink_prev(void);
int bt_sink_play(void);
int bt_sink_pause(void);
int bt_sink_get_track_info(char **title, char **artist);
int bt_sink_get_track_time(int *pos, int *time);
int bt_sink_get_vol(int *vol);

#endif

