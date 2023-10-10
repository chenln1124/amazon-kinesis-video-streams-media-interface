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

#include <stdlib.h>
#include <string.h>

#include "com/amazonaws/kinesis/video/capturer/VideoCapturer.h"

#include "T31Common.h"
#include "sample-common.h"

#define T31_HANDLE_GET(x) T31VideoCapturer* t31Handle = (T31VideoCapturer*) ((x))

typedef struct {
    VideoCapturerStatus status;
    VideoCapability capability;
    VideoFormat format;
    VideoResolution resolution;
    uint8_t channelNum;
} T31VideoCapturer;

extern ipc_av_config av_config[E_HAL_AV_CHN_MAX];

static int setStatus(VideoCapturerHandle handle, const VideoCapturerStatus newStatus)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (newStatus != t31Handle->status) {
        t31Handle->status = newStatus;
        LOG("VideoCapturer new status[%d]", newStatus);
    }

    return 0;
}

VideoCapturerHandle videoCapturerCreate(void)
{
    T31VideoCapturer* t31Handle = NULL;

    if (!(t31Handle = (T31VideoCapturer*) malloc(sizeof(T31VideoCapturer)))) {
        LOG("OOM");
        return NULL;
    }

    memset(t31Handle, 0, sizeof(T31VideoCapturer));

    initAVConfig();

    // Now implementation supports H.264, RAW(NV12), 1080p, 720p, 480p, 360p and 320p
    t31Handle->capability.formats = (1 << (VID_FMT_H264 - 1)) | (1 << (VID_FMT_RAW - 1));
    t31Handle->capability.resolutions =
        (1 << (VID_RES_1080P - 1)) | (1 << (VID_RES_720P - 1)) | (1 << (VID_RES_480P - 1)) | (1 << (VID_RES_360P - 1));

    setStatus((VideoCapturerHandle) t31Handle, VID_CAP_STATUS_STREAM_OFF);

    return (VideoCapturerHandle) t31Handle;
}

VideoCapturerStatus videoCapturerGetStatus(const VideoCapturerHandle handle)
{
    if (!handle) {
        return VID_CAP_STATUS_NOT_READY;
    }

    T31_HANDLE_GET(handle);
    return t31Handle->status;
}

int videoCapturerGetCapability(const VideoCapturerHandle handle, VideoCapability* pCapability)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (!pCapability) {
        return -EAGAIN;
    }

    *pCapability = t31Handle->capability;

    return 0;
}

int videoCapturerSetFormat(VideoCapturerHandle handle, const VideoFormat format, const VideoResolution resolution)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, VID_CAP_STATUS_STREAM_OFF);

    switch (resolution) {
        case VID_RES_1080P:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.width = VIDEO_WIDTH_1080P_2M;
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.height = VIDEO_HEIGHT_1080P_2M;
            break;
        case VID_RES_720P:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.width = VIDEO_WIDTH_720P_1M;
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.height = VIDEO_HEIGHT_720P_1M;
            break;
        case VID_RES_480P:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.width = VIDEO_WIDTH_720X480;
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.height = VIDEO_HEIGHT_720X480;
            break;
        case VID_RES_360P:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.width = VIDEO_WIDTH_640X360;
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.height = VIDEO_HEIGHT_640X360;
            break;

        default:
            LOG("Unsupported resolution %d", resolution);
            return -EINVAL;
    }

    switch (format) {
        case VID_FMT_H264:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.enc_type = IPC_VIDEO_ENCTYPE_H264;
            break;
        case VID_FMT_RAW:
            av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf.enc_type = IPC_VIDEO_ENCTYPE_YUV;
            break;

        default:
            LOG("Unsupported format %d", format);
            return -EINVAL;
    }

    t31Handle->format = format;
    t31Handle->resolution = resolution;

    return Hal_video_channel_params_reconfig(E_HAL_VIDEO_ENC_CHN_MAIN, av_config[E_HAL_VIDEO_ENC_CHN_MAIN].video_conf);
}

int videoCapturerGetFormat(const VideoCapturerHandle handle, VideoFormat* pFormat, VideoResolution* pResolution)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    *pFormat = t31Handle->format;
    *pResolution = t31Handle->resolution;

    return 0;
}

int videoCapturerAcquireStream(VideoCapturerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    return setStatus(handle, VID_CAP_STATUS_STREAM_ON);
}

int videoCapturerGetFrame(VideoCapturerHandle handle, void* pFrameDataBuffer, const size_t frameDataBufferSize, uint64_t* pTimestamp,
                          size_t* pFrameSize)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, VID_CAP_STATUS_STREAM_ON);

    if (!pFrameDataBuffer || !pTimestamp || !pFrameSize) {
        return -EINVAL;
    }

    int ret = 0;

    if (t31Handle->format == VID_FMT_RAW) {

    } else {
        char frame_type[5][10] = {"", "I", "P", "B", "A"};
        Hal_frame_head_t frame_head = {0};

        memset(&frame_head, 0, sizeof(frame_head));
        memset(pFrameDataBuffer, 0, frameDataBufferSize);
        ret = Hal_get_stream_from_codec(E_HAL_VIDEO_ENC_CHN_MAIN, &frame_head, pFrameDataBuffer, frameDataBufferSize, 20);
        if (ret == 0) {
            *pFrameSize = frame_head.frame_size;
            *pTimestamp = getEpochTimestampInUs();
            // sdk_stream_write_stream("./main.h264", pFrameDataBuffer, frame_head.frame_size);
            // printf("video stream, channel:main frame_type:%s width:%d height:%d frame_rate:%d frame_size:%d frame_pts:%lld frame_no:%d, timestamp: %lld\n",
            //     frame_type[frame_head.frame_type], frame_head.width, frame_head.height, frame_head.frame_rate, frame_head.frame_size, frame_head.pts, frame_head.frame_no, *pTimestamp);
        }
        else {
            ret = -EAGAIN;
        }
    }

    return ret;
}

int videoCapturerReleaseStream(VideoCapturerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    return setStatus(handle, VID_CAP_STATUS_STREAM_OFF);
}

void videoCapturerDestroy(VideoCapturerHandle handle)
{
    if (!handle) {
        return;
    }
    T31_HANDLE_GET(handle);

    deInitAVConfig();

    if (t31Handle->status == VID_CAP_STATUS_STREAM_ON) {
        videoCapturerReleaseStream(handle);
    }

    setStatus(handle, VID_CAP_STATUS_NOT_READY);

    free(handle);
}
