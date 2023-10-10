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

#include "com/amazonaws/kinesis/video/player/AudioPlayer.h"

#include "T31Common.h"
#include "sample-common.h"

#define T31_HANDLE_GET(x) T31AudioPlayer* t31Handle = (T31AudioPlayer*) ((x))

typedef struct {
    AudioPlayerStatus status;
    AudioCapability capability;
    AudioFormat format;
    AudioChannel channel;
    AudioBitDepth bitDepth;
    AudioSampleRate sampleRate;
} T31AudioPlayer;

extern ipc_av_config av_config[E_HAL_AV_CHN_MAX];

static int setStatus(AudioPlayerHandle handle, const AudioPlayerStatus newStatus)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (newStatus != t31Handle->status) {
        t31Handle->status = newStatus;

        LOG("AudioPlayer new status[%d]", newStatus);
    }

    return 0;
}

AudioPlayerHandle audioPlayerCreate(void)
{
    T31AudioPlayer* t31Handle = NULL;

    if (!(t31Handle = (T31AudioPlayer*) malloc(sizeof(T31AudioPlayer)))) {
        LOG("OOM");
        return NULL;
    }

    memset(t31Handle, 0, sizeof(T31AudioPlayer));

    // Now implementation supports raw PCM, G.711 ALAW and ULAW, MONO, 8k, 16 bits
    t31Handle->capability.formats = (1 << (AUD_FMT_G711A - 1)) | (1 << (AUD_FMT_G711U - 1)) | (1 << (AUD_FMT_PCM - 1)) | (1 << (AUD_FMT_AAC - 1));
    t31Handle->capability.channels = (1 << (AUD_CHN_MONO - 1));
    t31Handle->capability.sampleRates = (1 << (AUD_SAM_8K - 1));
    t31Handle->capability.bitDepths = (1 << (AUD_BIT_16 - 1));

    setStatus((AudioPlayerHandle) t31Handle, AUD_PLY_STATUS_STREAM_OFF);

    return (AudioPlayerHandle) t31Handle;
}

int audioPlayerGetCapability(const AudioPlayerHandle handle, AudioCapability* pCapability)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    if (!pCapability) {
        return -EAGAIN;
    }

    *pCapability = t31Handle->capability;

    return 0;
}

int audioPlayerSetFormat(AudioPlayerHandle handle, const AudioFormat format, const AudioChannel channel, const AudioSampleRate sampleRate,
                         const AudioBitDepth bitDepth)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, AUD_PLY_STATUS_STREAM_OFF);

    switch (format) {
        case AUD_FMT_PCM:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_PCM;
            break;
        case AUD_FMT_G711A:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_G711A;
            break;
        case AUD_FMT_G711U:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_G711U;
            break;
        case AUD_FMT_AAC:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.enc_type = IPC_AUDIO_ENCTYPE_AACLC;
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
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.samplerate = AUDIO_SAMPLE_RATE_8K;
            break;
        case AUD_SAM_16K:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.samplerate = AUDIO_SAMPLE_RATE_16K;
            break;

        default:
            LOG("Unsupported sample rate %d", sampleRate);
            return -EINVAL;
    }

    switch (bitDepth) {
        case AUD_BIT_16:
            av_config[E_HAL_AUDIO_AO_CHN].audio_conf.bitwidth = AUDIO_BITWIDTH_16;
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

int audioPlayerGetFormat(const AudioPlayerHandle handle, AudioFormat* pFormat, AudioChannel* pChannel, AudioSampleRate* pSampleRate,
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

int audioPlayerAcquireStream(AudioPlayerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    return setStatus(handle, AUD_PLY_STATUS_STREAM_ON);
}

int audioPlayerWriteFrame(AudioPlayerHandle handle, void* pData, const size_t size)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    T31_HANDLE_STATUS_CHECK(t31Handle, AUD_PLY_STATUS_STREAM_ON);

    if (!pData) {
        return -EINVAL;
    }

    int ret = 0;
    IPC_AUDIO_ENCTYPE audio_type = IPC_AUDIO_ENCTYPE_G711A;

    switch (t31Handle->format) {
        case AUD_FMT_PCM:
            audio_type = IPC_AUDIO_ENCTYPE_PCM;
            break;
        case AUD_FMT_G711A:
            audio_type = IPC_AUDIO_ENCTYPE_G711A;
            break;
        case AUD_FMT_G711U:
            audio_type = IPC_AUDIO_ENCTYPE_G711U;
            break;
        case AUD_FMT_AAC:
            audio_type = IPC_AUDIO_ENCTYPE_AACLC;
            break;

        default:
            LOG("Unsupported format %d", t31Handle->format);
            return -EINVAL;
    }

    ret = Hal_speaker_play_packet(audio_type, (unsigned char *)pData, size);
    if (ret == 0) {
        // printf(" Hal_speaker_play_packet success! \n ");
    }
    else {
        ret = -EAGAIN;
    }

    return ret;
}

int audioPlayerReleaseStream(AudioPlayerHandle handle)
{
    T31_HANDLE_NULL_CHECK(handle);
    T31_HANDLE_GET(handle);

    return setStatus(handle, AUD_PLY_STATUS_STREAM_OFF);
}

void audioPlayerDestroy(AudioPlayerHandle handle)
{
    if (!handle) {
        return;
    }
    T31_HANDLE_GET(handle);

    if (t31Handle->status == AUD_PLY_STATUS_STREAM_ON) {
        audioPlayerReleaseStream(handle);
    }

    setStatus(handle, AUD_PLY_STATUS_NOT_READY);

    free(handle);
}
