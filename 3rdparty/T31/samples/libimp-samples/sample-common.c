/*
 * Copyright 2021 Amazon.com, Inc. or its affiliates. All Rights Reserved.
 *
 * Licensed under the Apache License, Version 2.0 (the "License").
 * You may not use this file except in compliance with the License.
 * A copy of the License is located at
 *
 *  http://aws.amazon.com/apache2.0
 *
 * or in the "license" file accompanying this file. This file is distributed
 * on an "AS IS" BASIS, WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either
 * express or implied. See the License for the specific language governing
 * permissions and limitations under the License.
 */

#include "sample-common.h"
#include <sys/ioctl.h>

#define MAX_RES_WIDTH          VIDEO_WIDTH_1080P_2M
#define MAX_RES_HEIGHT         VIDEO_HEIGHT_1080P_2M

#define IOCTRL_PTZ_CMD(x)      ('p'<<8 | x)
#define PTZ_STATUS             18

#define HAL_GPIO_LED_RED       T31_GPIO_PA(17)
#define HAL_GPIO_LED_BLUE      T31_GPIO_PA(16)
#define HAL_GPIO_IRLED         T31_GPIO_PB(27)
#define HAL_GPIO_IRCUT_A       T31_GPIO_PB(25)
#define HAL_GPIO_IRCUT_B       T31_GPIO_PB(26)
#define HAL_GPIO_RESET         T31_GPIO_PB(18)
#define HAL_GPIO_WIFI_POWER    T31_GPIO_PA(10)
#define HAL_GPIO_SPEAK_POWER   T31_GPIO_PA(9)

ipc_av_config av_config[E_HAL_AV_CHN_MAX] = {
    /* Main Channel, E_HAL_VIDEO_ENC_CHN_MAIN */
    {
        1,
        { .video_conf = {
            IPC_VIDEO_ENCTYPE_H264,
            E_IPC_RCMODE_AVBR,
            VIDEO_BITRATE_1Mbps,
            25,
            25,
            VIDEO_WIDTH_1080P_2M,
            VIDEO_HEIGHT_1080P_2M,
            IPC_VIDEO_PROFILE_H264_MAIN
          }
        },
        NULL,
        NULL,
        0
    },
    /* Sub Channel, E_HAL_VIDEO_ENC_CHN_SUB */
    {
        1,
        { .video_conf = {
            IPC_VIDEO_ENCTYPE_H264,
            E_IPC_RCMODE_AVBR,
            VIDEO_BITRATE_600Kbps,
            25,
            25,
            VIDEO_WIDTH_640X360,
            VIDEO_HEIGHT_640X360,
            IPC_VIDEO_PROFILE_H264_MAIN
          }
        },
        NULL,
        NULL,
        0
    },
    /* Snapshot JPEG Channel, E_HAL_VIDEO_ENC_CHN_JPEG */
    {
        1,
        { .video_conf = {
            IPC_VIDEO_ENCTYPE_MJPEG,
            E_IPC_RCMODE_MJPEGFIXQP,
            VIDEO_BITRATE_1Mbps,
            10,
            10,
            VIDEO_WIDTH_352X240,
            VIDEO_HEIGHT_352X240,
            IPC_VIDEO_PROFILE_JPEG_MAIN
          }
        },
        NULL,
        NULL,
        0
    },
    /* Algorithm YUV Channel, E_HAL_VIDEO_ENC_CHN_YUV */
    {
        1,
        { .video_conf = {
            IPC_VIDEO_ENCTYPE_YUV,
            0,
            0,
            0,
            0,
            VIDEO_WIDTH_352X288,
            VIDEO_HEIGHT_352X288,
            0
          }
        },
        NULL,
        NULL,
        0
    },
    /* AI Channel, E_HAL_AUDIO_AI_CHN_MAIN */
    {
        1,
        { .audio_conf = {
            IPC_AUDIO_ENCTYPE_G711A,
            AUDIO_SAMPLE_RATE_8K,
            AUDIO_BITWIDTH_16,
            640
          }
        },
        NULL,
        NULL,
        0
    },
    /* AI Channel, E_HAL_AUDIO_AI_CHN_SUB */
    {
        0,
        { .audio_conf = {
            IPC_AUDIO_ENCTYPE_AACLC,
            AUDIO_SAMPLE_RATE_8K,
            AUDIO_BITWIDTH_16
          }
        },
        NULL,
        NULL,
        0
    },
    /* AO Channel, E_HAL_AUDIO_AO_CHN */
    {
        1,
        { .audio_conf = {
            IPC_AUDIO_ENCTYPE_G711A,
            AUDIO_SAMPLE_RATE_8K,
            AUDIO_BITWIDTH_16
          }
        },
        NULL,
        NULL,
        0
    }
};

typedef struct ptz_status_params
{
	int is_running;
} ptz_status_params;

static int sample_fd = 0;
static int ptz_done = 0;
static int Sample_PTZ_is_running(void)
{
	if(!ptz_done)
		return -1;
	
	if(sample_fd >= 0)
	{
		ptz_status_params status;
		ioctl(sample_fd, IOCTRL_PTZ_CMD(PTZ_STATUS), &status);
		return status.is_running;
	}
	return 0;
}

static int Sample_GPIO_init(void)
{
    Hal_gpio_config_t gpio_cfg[E_HAL_GPIO_MAX] = {0};
    gpio_cfg[E_HAL_GPIO_LED_RED].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_LED_RED].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_LED_RED].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_LED_RED].pinNumber[0] = HAL_GPIO_LED_RED;
    gpio_cfg[E_HAL_GPIO_LED_RED].eDirControl[0] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_LED_RED].eValidLevel[0] = E_HAL_GPIO_LEVEL_LOW;
    gpio_cfg[E_HAL_GPIO_LED_RED].bDefaultOn[0] = 1;

    gpio_cfg[E_HAL_GPIO_LED_BLUE].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].pinNumber[0] = HAL_GPIO_LED_BLUE;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].eDirControl[0] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].eValidLevel[0] = E_HAL_GPIO_LEVEL_LOW;
    gpio_cfg[E_HAL_GPIO_LED_BLUE].bDefaultOn[0] = 0;

    gpio_cfg[E_HAL_GPIO_IRLED].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_IRLED].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_IRLED].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_IRLED].pinNumber[0] = HAL_GPIO_IRLED;
    gpio_cfg[E_HAL_GPIO_IRLED].eDirControl[0] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_IRLED].eValidLevel[0] = E_HAL_GPIO_LEVEL_HIGH;
    gpio_cfg[E_HAL_GPIO_IRLED].bDefaultOn[0] = 0;

    gpio_cfg[E_HAL_GPIO_IRCUT].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_IRCUT].gpioCtrlPinNumber = 2;
    gpio_cfg[E_HAL_GPIO_IRCUT].extraCfg.eIrcutPinMode = E_HAL_IRCUT_DOUBLE_PIN_CTRL;
    gpio_cfg[E_HAL_GPIO_IRCUT].muxCtrlRegOffset[E_HAL_GPIO_IRCUT_AIN] = -1;
    gpio_cfg[E_HAL_GPIO_IRCUT].muxCtrlRegOffset[E_HAL_GPIO_IRCUT_BIN] = -1;
    gpio_cfg[E_HAL_GPIO_IRCUT].pinNumber[E_HAL_GPIO_IRCUT_AIN] = HAL_GPIO_IRCUT_A;
    gpio_cfg[E_HAL_GPIO_IRCUT].pinNumber[E_HAL_GPIO_IRCUT_BIN] = HAL_GPIO_IRCUT_B;
    gpio_cfg[E_HAL_GPIO_IRCUT].eDirControl[E_HAL_GPIO_IRCUT_AIN] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_IRCUT].eDirControl[E_HAL_GPIO_IRCUT_BIN] = E_HAL_GPIO_DIR_OUTPUT;

    gpio_cfg[E_HAL_GPIO_RESET].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_RESET].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_RESET].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_RESET].pinNumber[0] = HAL_GPIO_RESET;
    gpio_cfg[E_HAL_GPIO_RESET].eDirControl[0] = E_HAL_GPIO_DIR_INPUT;
    gpio_cfg[E_HAL_GPIO_RESET].eValidLevel[0] = E_HAL_GPIO_LEVEL_LOW;

    gpio_cfg[E_HAL_GPIO_WIFI_POWER].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].pinNumber[0] = HAL_GPIO_WIFI_POWER;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].eDirControl[0] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].eValidLevel[0] = E_HAL_GPIO_LEVEL_HIGH;
    gpio_cfg[E_HAL_GPIO_WIFI_POWER].bDefaultOn[0] = 1;

    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].bSupport = 1;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].gpioCtrlPinNumber = 1;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].muxCtrlRegOffset[0] = -1;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].pinNumber[0] = HAL_GPIO_SPEAK_POWER;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].eDirControl[0] = E_HAL_GPIO_DIR_OUTPUT;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].eValidLevel[0] = E_HAL_GPIO_LEVEL_HIGH;
    gpio_cfg[E_HAL_GPIO_SPEAK_POWER].bDefaultOn[0] = 0;
    Hal_GPIO_init(gpio_cfg, Sample_PTZ_is_running);
    return 0;
}

int initAVConfig(void)
{
    int ret = 0;

    /* Debug log */
    Hal_SYSLOG_Set_LogPrintLevel(LOG_TRACE);

    /* GPIO init */
    Sample_GPIO_init();

    ret |= Hal_init(MAX_RES_WIDTH, MAX_RES_HEIGHT, av_config);

    ret |= Hal_Mic_init_divided_levels(5);
    ret |= Hal_Speaker_init_divided_levels(5);
    ret |= Hal_Mic_set_vol(5);
    ret |= Hal_Speaker_set_vol(5);

    return ret;
}

int deInitAVConfig(void)
{
    return Hal_uninit();
}

__attribute__((weak)) uint64_t getEpochTimestampInUs(void)
{
    uint64_t timestamp = 0;

    struct timeval tv;
    gettimeofday(&tv, NULL);
    timestamp = (uint64_t) (tv.tv_sec) * 1000 * 1000 + (uint64_t) (tv.tv_usec);

    return timestamp;
}

int sdk_stream_write_stream(char *file_name, char *buf, int len)
{
    FILE *fp = fopen(file_name, "a+");
    if(NULL == fp)
        return -1;

    fwrite(buf, 1, len, fp);
    fclose(fp);
    fp = NULL;

    return 0;
}
