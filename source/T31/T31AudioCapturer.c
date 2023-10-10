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

#include "com/amazonaws/kinesis/video/capturer/AudioCapturer.h"

#include "T31Common.h"
#include "sample-common.h"

#define T31_HANDLE_GET(x) T31AudioCapturer* t31Handle = (T31AudioCapturer*) ((x))

typedef struct {
    AudioCapturerStatus status;
    AudioCapability capability;
    AudioFormat format;
    AudioChannel channel;
    AudioBitDepth bitDepth;
    AudioSampleRate sampleRate;
} T31AudioCapturer;

extern ipc_av_config av_config[E_HAL_AV_CHN_MAX];

static int setStatus(AudioCapturerHandle handle, const AudioCapturerStatus newStatus)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (newStatus != t31Handle->status) {
        t31Handle->status = newStatus;
        LOG("AudioCapturer new status[%d]", newStatus);
    }

    return 0;
}

AudioCapturerHandle audioCapturerCreate(void)
{
    T31AudioCapturer* t31Handle = NULL;

    if (!(t31Handle = (T31AudioCapturer*) malloc(sizeof(T31AudioCapturer)))) {
        LOG("OOM");
        return NULL;
    }

    memset(t31Handle, 0, sizeof(T31AudioCapturer));

    // Now implementation supports raw PCM, G.711 ALAW and ULAW, MONO, 8k/16k, 16 bits
    t31Handle->capability.formats = (1 << (AUD_FMT_G711A - 1)) | (1 << (AUD_FMT_G711U - 1)) | (1 << (AUD_FMT_PCM - 1)) | (1 << (AUD_FMT_AAC - 1));
    t31Handle->capability.channels = (1 << (AUD_CHN_MONO - 1));
    t31Handle->capability.sampleRates = (1 << (AUD_SAM_8K - 1)) | (1 << (AUD_SAM_16K - 1));
    t31Handle->capability.bitDepths = (1 << (AUD_BIT_16 - 1));

    setStatus((AudioCapturerHandle) t31Handle, AUD_CAP_STATUS_STREAM_OFF);

    return (AudioCapturerHandle) t31Handle;
}

AudioCapturerStatus audioCapturerGetStatus(const AudioCapturerHandle handle)
{
    if (!handle) {
        return AUD_CAP_STATUS_NOT_READY;
    }

    T31_HANDLE_GET(handle);
    return t31Handle->status;
}

int audioCapturerGetCapability(const AudioCapturerHandle handle, AudioCapability* pCapability)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (!pCapability) {
        return -EINVAL;
    }

    *pCapability = t31Handle->capability;

    return 0;
}

int audioCapturerSetFormat(AudioCapturerHandle handle, const AudioFormat format, const AudioChannel channel, const AudioSampleRate sampleRate,
                           const AudioBitDepth bitDepth)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, AUD_CAP_STATUS_STREAM_OFF);

    switch (format) {
        case AUD_FMT_G711A:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_G711A;
            break;
        case AUD_FMT_G711U:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_G711U;
            break;
        case AUD_FMT_PCM:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_PCM;
            break;
        case AUD_FMT_AAC:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_AACLC;
            break;

        default:
            LOG("Unsupported format %d", format);
            return -EINVAL;
    }

    switch (channel) {
        case AUD_CHN_MONO:
            break;

        default:
            LOG("Unsupported channel num %d", channel);
            return -EINVAL;
    }

    switch (sampleRate) {
        case AUD_SAM_8K:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.samplerate = AUDIO_SAMPLE_RATE_8K;
            break;
        case AUD_SAM_16K:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.samplerate = AUDIO_SAMPLE_RATE_16K;
            break;

        default:
            LOG("Unsupported sample rate %d", sampleRate);
            return -EINVAL;
    }

    switch (bitDepth) {
        case AUD_BIT_16:
            av_config[E_HAL_AUDIO_AI_CHN_MAIN].audio_conf.bitwidth = AUDIO_BITWIDTH_16;
            break;

        default:
            LOG("Unsupported bit depth %d", bitDepth);
            return -EINVAL;
    }

    t31Handle->format = format;
    t31Handle->channel = channel;
    t31Handle->sampleRate = sampleRate;
    t31Handle->bitDepth = bitDepth;

    return 0;
}

int audioCapturerGetFormat(const AudioCapturerHandle handle, AudioFormat* pFormat, AudioChannel* pChannel, AudioSampleRate* pSampleRate,
                           AudioBitDepth* pBitDepth)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    *pFormat = t31Handle->format;
    *pChannel = t31Handle->channel;
    *pSampleRate = t31Handle->sampleRate;
    *pBitDepth = t31Handle->bitDepth;

    return 0;
}

int audioCapturerAcquireStream(AudioCapturerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    return setStatus(handle, AUD_CAP_STATUS_STREAM_ON);
}

int audioCapturerGetFrame(AudioCapturerHandle handle, void* pFrameDataBuffer, const size_t frameDataBufferSize, uint64_t* pTimestamp,
                          size_t* pFrameSize)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, AUD_CAP_STATUS_STREAM_ON);

    if (!pFrameDataBuffer || !pTimestamp || !pFrameSize) {
        return -EINVAL;
    }

    int ret = 0;

    char frame_type[5][10] = {"", "I", "P", "B", "A"};
    Hal_frame_head_t frame_head = {0};

    memset(&frame_head, 0, sizeof(frame_head));
    memset(pFrameDataBuffer, 0, frameDataBufferSize);
    ret = Hal_get_stream_from_codec(E_HAL_AUDIO_AI_CHN_MAIN, &frame_head, pFrameDataBuffer, frameDataBufferSize, 20);
    if (ret == 0) {
        *pFrameSize = frame_head.frame_size;
        *pTimestamp = getEpochTimestampInUs();
        // sdk_stream_write_stream("./audio.aac", pFrameDataBuffer, frame_head.frame_size);
        // printf("audio stream, channel:main frame_type:%s frame_size:%d frame_pts:%lld frame_no:%d, timestamp: %lld\n",
        //     frame_type[frame_head.frame_type], frame_head.frame_size, frame_head.pts, frame_head.frame_no, *pTimestamp);
    }
    else {
        ret = -EAGAIN;
    }

    return ret;
}

int audioCapturerReleaseStream(AudioCapturerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, AUD_CAP_STATUS_STREAM_ON);

    return setStatus(handle, AUD_CAP_STATUS_STREAM_OFF);
}

void audioCapturerDestroy(AudioCapturerHandle handle)
{
    if (!handle) {
        return;
    }
    T31_HANDLE_GET(handle);

    if (t31Handle->status == AUD_CAP_STATUS_STREAM_ON) {
        audioCapturerReleaseStream(handle);
    }

    setStatus(handle, AUD_CAP_STATUS_NOT_READY);

    free(handle);
}
