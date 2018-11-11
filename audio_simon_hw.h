/******************************************************************************
 *
 *  Copyright (C) 2009-2012 Broadcom Corporation
 *
 *  Licensed under the Apache License, Version 2.0 (the "License");
 *  you may not use this file except in compliance with the License.
 *  You may obtain a copy of the License at:
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS,
 *  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 *
 ******************************************************************************/

/*****************************************************************************
 *
 *  Filename:      audio_simon_hw.h
 *
 *  Description:
 *
 *****************************************************************************/

#ifndef AUDIO_SIMON_HW_H
#define AUDIO_SIMON_HW_H

/*****************************************************************************
**  Constants & Macros
******************************************************************************/

#define A2DP_AUDIO_HARDWARE_INTERFACE "audio.simon"
#define A2DP_CTRL_PATH "/data/misc/bluedroid/.simon_ctrl"
#define A2DP_DATA_PATH "/data/misc/bluedroid/.simon_data"

#define AUDIO_STREAM_DEFAULT_RATE          44100
#define AUDIO_STREAM_DEFAULT_FORMAT        AUDIO_FORMAT_PCM_16_BIT
#define AUDIO_STREAM_DEFAULT_CHANNEL_FLAG  AUDIO_CHANNEL_OUT_STEREO
#define AUDIO_STREAM_OUTPUT_BUFFER_SZ      (20*512)
#define AUDIO_SKT_DISCONNECTED             (-1)

/*****************************************************************************
**  Constants & Macros
******************************************************************************/

#define CTRL_CHAN_RETRY_COUNT 3
#define USEC_PER_SEC 1000000L

#define CASE_RETURN_STR(const) case const: return #const;

#define FNLOG()             ALOGV("%s", __FUNCTION__);
#define DEBUG(fmt, ...)     ALOGV("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define INFO(fmt, ...)      ALOGI("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)
#define ERROR(fmt, ...)     ALOGE("%s: " fmt,__FUNCTION__, ## __VA_ARGS__)

#define ASSERTC(cond, msg, val) if (!(cond)) {ERROR("### ASSERT : %s line %d %s (%d) ###", __FILE__, __LINE__, msg, val);}


#ifdef DEBUG_CUSTOMER_AUDIO_DEVICE
	#define TRACE_LOG ALOGI
#else
	#define TRACE_LOG(fmt, args...)
#endif

#define PCM_16K          16000
#define PCM_48K          48000
#define BUFFER_IN_SIZE   160 //  5 ms
#define BUFFER_OUT_SIZE  768 //  5 ms


/*****************************************************************************
**  Local type definitions
******************************************************************************/

struct stub_audio_device {
    struct audio_hw_device device;
};

struct stub_stream_out {
    struct audio_stream_out stream;
};

struct stub_stream_in {
    struct audio_stream_in stream;
};


/*****************************************************************************
**  Type definitions for callback functions
******************************************************************************/

/*****************************************************************************
**  Type definitions and return values
******************************************************************************/

/*****************************************************************************
**  Extern variables and functions
******************************************************************************/

/*****************************************************************************
**  Functions
******************************************************************************/


/*****************************************************************************
**
** Function
**
** Description
**
** Returns
**
******************************************************************************/

#endif /* A2DP_AUDIO_HW_H */

