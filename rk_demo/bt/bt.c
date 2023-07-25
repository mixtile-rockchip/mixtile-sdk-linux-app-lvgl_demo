#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <RkBtBase.h>
#include <RkBtSink.h>
#include <RkBle.h>

#define BLE_UUID_SEND       "dfd4416e-1810-47f7-8248-eb8be3dc47f9"
#define BLE_UUID_RECV       "9884d812-1810-4a24-94d3-b2c11a851fac"
#define SERVICE_UUID        "00001910-0000-1000-8000-00805f9b34fb"

static RkBtContent bt_content;
static volatile bool gonff = false;
static volatile bool sink_started = false;
static RK_BT_SINK_STATE sink_state = RK_BT_SINK_STATE_IDLE;
static BtTrackInfo g_track_info;
static bool track_changed = 0;
static int g_pos, g_time;
static bool time_changed = 0;
static int g_volume;
static bool vol_changed = 0;

bool bt_sink_is_started(void)
{
    return sink_started;
}

bool bt_is_state_on(void)
{
    return gonff;
}

RK_BT_SINK_STATE bt_sink_state(void)
{
    return sink_state;
}

static int bt_sink_callback(RK_BT_SINK_STATE state)
{
    sink_state = state;
    switch (state)
    {
    case RK_BT_SINK_STATE_IDLE:
        printf("++++++++++++ BT SINK EVENT: idle ++++++++++\n");
        break;
    case RK_BT_SINK_STATE_CONNECT:
        printf("++++++++++++ BT SINK EVENT: connect sucess ++++++++++\n");
        break;
    case RK_BT_SINK_STATE_DISCONNECT:
        printf("++++++++++++ BT SINK EVENT: disconnected ++++++++++\n");
        break;
    case RK_BT_SINK_STATE_PLAY:
        printf("++++++++++++ BT SINK EVENT: playing ++++++++++\n");
        break;
    case RK_BT_SINK_STATE_PAUSE:
        printf("++++++++++++ BT SINK EVENT: paused ++++++++++\n");
        break;
    case RK_BT_SINK_STATE_STOP:
        printf("++++++++++++ BT SINK EVENT: stoped ++++++++++\n");
        break;
    case RK_BT_A2DP_SINK_STARTED:
        printf("++++++++++++ BT A2DP SINK STATE: started ++++++++++\n");
        sink_started = true;
        break;
    case RK_BT_A2DP_SINK_SUSPENDED:
        printf("++++++++++++ BT A2DP SINK STATE: suspended ++++++++++\n");
        sink_started = false;
        break;
    case RK_BT_A2DP_SINK_STOPPED:
        printf("++++++++++++ BT A2DP SINK STATE: stoped ++++++++++\n");
        break;
    }

    return 0;
}

static void bt_sink_position_change_callback(const char *bd_addr, int song_len, int song_pos)
{
    printf("++++++++ bt sink position change ++++++++\n");
    printf("    remote device address: %s\n", bd_addr);
    printf("    song_len: %d, song_pos: %d\n", song_len, song_pos);
    g_pos = song_pos;
    g_time = song_len;
    time_changed = 1;
}

static void bt_sink_track_change_callback(const char *bd_addr, BtTrackInfo track_info)
{
    int playing_time;

    printf("++++++++ bt sink track change ++++++++\n");
    printf("    remote device address: %s\n", bd_addr);
    printf("    title:  [%s]\n", track_info.title);
    printf("    artist: [%s]\n", track_info.artist);
    printf("    album:  [%s]\n", track_info.album);
    printf("    genre:  [%s]\n", track_info.genre);
    printf("    num_tracks: [%s]\n", track_info.num_tracks);
    printf("    track_num:  [%s]\n", track_info.track_num);
    printf("    playing_time: [%s]\n", track_info.playing_time);
    playing_time = atoi(track_info.playing_time);
    if (playing_time)
    {
        if (strlen(track_info.title))
        {
            memcpy(g_track_info.title, track_info.title, sizeof(g_track_info.title));
            track_changed = 1;
        }
        if (strlen(track_info.artist))
        {
            memcpy(g_track_info.artist, track_info.artist, sizeof(g_track_info.artist));
            track_changed = 1;
        }
    }
    else
    {
        snprintf(g_track_info.title, sizeof(g_track_info.title), "媒体音频");
        snprintf(g_track_info.artist, sizeof(g_track_info.artist), " ");
        track_changed = 1;
    }
}

int bt_sink_get_track_info(char **title, char **artist)
{
    if (!track_changed)
    {
        *title = NULL;
        *artist = NULL;
        return 0;
    }
    track_changed = 0;

    *title = strdup(g_track_info.title);
    *artist = strdup(g_track_info.artist);

    return 1;
}

int bt_sink_get_track_time(int *pos, int *time)
{
    if (!time_changed)
    {
        return 0;
    }
    time_changed = 0;

    *pos = g_pos;
    *time = g_time;

    return 1;
}

int bt_sink_get_vol(int *vol)
{
    if (!vol_changed)
    {
        return 0;
    }
    vol_changed = 0;

    *vol = g_volume;

    return 1;
}

static void bt_sink_volume_callback(int volume)
{
    printf("++++++++ bt sink volume change, volume: %d ++++++++\n", volume);
    g_volume = volume;
    vol_changed = 1;
}

static void bt_bond_state_cb(const char *bd_addr, const char *name, RK_BT_BOND_STATE state)
{
    switch (state)
    {
    case RK_BT_BOND_STATE_NONE:
        printf("++++++++++ BT BOND NONE: %s, %s ++++++++++\n", name, bd_addr);
        break;
    case RK_BT_BOND_STATE_BONDING:
        printf("++++++++++ BT BOND BONDING: %s, %s ++++++++++\n", name, bd_addr);
        break;
    case RK_BT_BOND_STATE_BONDED:
        printf("++++++++++ BT BONDED: %s, %s ++++++++++\n", name, bd_addr);
        break;
    }
}

static void bt_state_cb(RK_BT_STATE state)
{
    switch (state)
    {
    case RK_BT_STATE_TURNING_ON:
        printf("++++++++++ RK_BT_STATE_TURNING_ON ++++++++++\n");
        break;
    case RK_BT_STATE_ON:
        printf("++++++++++ RK_BT_STATE_ON ++++++++++\n");
        gonff = true;
        break;
    case RK_BT_STATE_TURNING_OFF:
        printf("++++++++++ RK_BT_STATE_TURNING_OFF ++++++++++\n");
        break;
    case RK_BT_STATE_OFF:
        printf("++++++++++ RK_BT_STATE_OFF ++++++++++\n");
        gonff = false;
        break;
    }
}

static void bt_ble_request_data_callback(const char *uuid)
{
    printf("=== %s uuid: %s===\n", __func__, uuid);
}

static void bt_ble_recv_data_callback(const char *uuid, char *data, int len)
{
    printf("=== %s uuid: %s===\n", __func__, uuid);
    for (int i = 0 ; i < len; i++)
    {
        printf("%02x ", data[i]);
    }
    printf("\n");
}

int bt_ble_init(void)
{
    int len, ble_name_len, remain_len;

    memset(&bt_content, 0, sizeof(RkBtContent));
    bt_content.bt_name = "ROCKCHIP_AUDIO";
    bt_content.ble_content.ble_name = "ROCKCHIP_AUDIO_BLE";
    bt_content.ble_content.server_uuid.uuid = SERVICE_UUID;
    bt_content.ble_content.server_uuid.len = UUID_128;
    bt_content.ble_content.chr_uuid[0].uuid = BLE_UUID_SEND;
    bt_content.ble_content.chr_uuid[0].len = UUID_128;
    bt_content.ble_content.chr_uuid[1].uuid = BLE_UUID_RECV;
    bt_content.ble_content.chr_uuid[1].len = UUID_128;
    bt_content.ble_content.chr_cnt = 2;

    bt_content.ble_content.advDataType = BLE_ADVDATA_TYPE_USER;

    //标识设备 LE 物理连接的功能
    bt_content.ble_content.advData[1] = 0x02;
    bt_content.ble_content.advData[2] = 0x01;
    bt_content.ble_content.advData[3] = 0x02;

    //service uuid(SERVICE_UUID)
    bt_content.ble_content.advData[4] = 0x03;
    bt_content.ble_content.advData[5] = 0x03;
    bt_content.ble_content.advData[6] = 0x10;
    bt_content.ble_content.advData[7] = 0x19;

    //ble name
    printf("ble_name_len: %s(%d)\n", bt_content.ble_content.ble_name, strlen(bt_content.ble_content.ble_name));
    ble_name_len = strlen(bt_content.ble_content.ble_name);
    remain_len = 31 - (bt_content.ble_content.advData[1] + 1)
                 - (bt_content.ble_content.advData[4] + 1);
    len = ble_name_len > remain_len ? remain_len : ble_name_len;
    bt_content.ble_content.advData[8] = len + 1;
    bt_content.ble_content.advData[9] = 0x09;
    memcpy(&bt_content.ble_content.advData[10], bt_content.ble_content.ble_name, len);

    bt_content.ble_content.advData[0] = bt_content.ble_content.advData[1] + 1
                                        + bt_content.ble_content.advData[4] + 1
                                        + bt_content.ble_content.advData[8] + 1;
    bt_content.ble_content.advDataLen = bt_content.ble_content.advData[0] + 1;

    //==========================rsp======================
    bt_content.ble_content.respData[1] = 0x16;  //长度
    bt_content.ble_content.respData[2] = 0xFF;  //字段类型

    /*厂商编码*/
    bt_content.ble_content.respData[3] = 0x46;
    bt_content.ble_content.respData[4] = 0x00;

    bt_content.ble_content.respData[5] = 0x02;  //项目代号长度

    /*项目代号*/
    bt_content.ble_content.respData[6] = 0x1c;
    bt_content.ble_content.respData[7] = 0x02;

    bt_content.ble_content.respData[8] = 0x04;  //版本号长度
    bt_content.ble_content.respData[9] = 'T';   //版本号类型
    /*版本号*/
    bt_content.ble_content.respData[10] = 0x01;
    bt_content.ble_content.respData[11] = 0x00;
    bt_content.ble_content.respData[12] = 0x00;

    bt_content.ble_content.respData[13] = 0x08; // SN长度
    /*SN号*/
    bt_content.ble_content.respData[14] = 0x54;
    bt_content.ble_content.respData[15] = 0x00;
    bt_content.ble_content.respData[16] = 0x00;
    bt_content.ble_content.respData[17] = 0x00;
    bt_content.ble_content.respData[18] = 0x00;
    bt_content.ble_content.respData[19] = 0x00;
    bt_content.ble_content.respData[20] = 0x00;
    bt_content.ble_content.respData[21] = 0x36;

    bt_content.ble_content.respData[22] = 0x01; //绑定信息长度
    bt_content.ble_content.respData[23] = 0x00; //绑定信息

    bt_content.ble_content.respData[0] = bt_content.ble_content.respData[1] + 1;  //长度
    bt_content.ble_content.respDataLen = bt_content.ble_content.respData[0] + 1;

    bt_content.ble_content.cb_ble_recv_fun = bt_ble_recv_data_callback;
    bt_content.ble_content.cb_ble_request_data = bt_ble_request_data_callback;
    rk_bt_register_state_callback(bt_state_cb);
    rk_bt_register_bond_callback(bt_bond_state_cb);
    return rk_bt_init(&bt_content);
}

int bt_ble_deinit(void)
{
    rk_bt_deinit();
}

int bt_sink_enable(void)
{
    rk_bt_sink_register_volume_callback(bt_sink_volume_callback);
    rk_bt_sink_register_track_callback(bt_sink_track_change_callback);
    rk_bt_sink_register_position_callback(bt_sink_position_change_callback);
    rk_bt_sink_register_callback(bt_sink_callback);

    return rk_bt_sink_open();
}

int bt_sink_disable(void)
{
    rk_bt_sink_close();
}

int bt_sink_disconnect(void)
{
    rk_bt_sink_disconnect();
}

int bt_sink_set_volume(int volume)
{
    return rk_bt_sink_set_volume(volume);
}

int bt_sink_next(void)
{
    return rk_bt_sink_next();
}

int bt_sink_prev(void)
{
    return rk_bt_sink_prev();
}

int bt_sink_play(void)
{
    return rk_bt_sink_play();
}

int bt_sink_pause(void)
{
    return rk_bt_sink_pause();
}

