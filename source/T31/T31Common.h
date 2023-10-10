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

#pragma once

#include <errno.h>
#include <stdio.h>
#include <pthread.h>

#define LOG(msg, ...) printf(msg "\n", ##__VA_ARGS__)

#define T31_HANDLE_NULL_CHECK(x)                                                                                                                     \
    if (!(x)) {                                                                                                                                      \
        return -EINVAL;                                                                                                                              \
    }
#define T31_HANDLE_STATUS_CHECK(t31Handle, expectedStatus)                                                                                           \
    if ((t31Handle)->status != (expectedStatus)) {                                                                                                   \
        return -EAGAIN;                                                                                                                              \
    }

#define T31_POLLING_STREAM_TIMEOUT_MS 1000
