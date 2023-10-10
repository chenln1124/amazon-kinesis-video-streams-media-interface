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

#include "gpio_description_t31.h"
#include "Hal_audio_input.h"
#include "Hal_audio_output.h"
#include "Hal_video_input.h"
#include "Hal_av_channel_params.h"
#include "Hal_main.h"
#include "Hal_log.h"
#include "Hal_gpio.h"

int initAVConfig(void);
int deInitAVConfig(void);
uint64_t getEpochTimestampInUs(void);
int sdk_stream_write_stream(char *file_name, char *buf, int len);
