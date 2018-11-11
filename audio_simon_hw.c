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
 *  Filename:      audio_Simon_hw.c
 *
 *  Description:   Implements hal for bluedroid simon's customer audio device
 *
 *****************************************************************************/

#include <errno.h>
#include <pthread.h>
#include <stdint.h>
#include <sys/time.h>
#include <sys/socket.h>
#include <sys/un.h>
#include <sys/poll.h>
#include <sys/errno.h>
#include <sys/stat.h>
#include <unistd.h>
#include <fcntl.h>
#include <cutils/str_parms.h>
#include <cutils/sockets.h>

#include <system/audio.h>
#include <hardware/audio.h>

#include <hardware/hardware.h>
#include "audio_simon_hw.h"

#define LOG_TAG "audio_simon_hw"
/* #define LOG_NDEBUG 0 */
#include <cutils/log.h>
#include <dlfcn.h>


/*****************************************************************************
**  Static functions
******************************************************************************/

static size_t out_get_buffer_size(const struct audio_stream *stream);

/*****************************************************************************
**  Externs
******************************************************************************/

typedef int (*fn_sbc_codec_init)();
typedef int (*fn_sbc_codec_proc)(unsigned char *pBuf, unsigned int BufLen);

void *hDll = NULL;
fn_sbc_codec_init sbc_codec_init = NULL;
fn_sbc_codec_proc sbc_codec_proc = NULL;

int load_customer_library()
{
    int ret = 0;

    if (!hDll) {
        hDll = dlopen("/system/lib/libsbcdec.so", RTLD_NOW);
        if (!hDll) {
            ALOGI("Fail to load libsbcdec.so file (%s)", dlerror());
        } else {
            sbc_codec_init = (fn_sbc_codec_init) dlsym(hDll, "sbc_codec_init");
            sbc_codec_proc = (fn_sbc_codec_proc) dlsym(hDll, "sbc_codec_proc");
        }
		
        if (sbc_codec_init && sbc_codec_proc) {
            ret = 1;
        } else {
            ALOGI("Load libsbcdec.so function fail");
        }
    }
	
    return ret;
}

/*****************************************************************************
**  Functions
******************************************************************************/

/*      show android version here !!!  by simon */

int android_hal_version(unsigned char ver[])
{

	ALOGI("Android HAL Version: %s",ver);

    return 1;
}

/*****************************************************************************
**
**  audio output callbacks
**
*****************************************************************************/
static uint32_t out_get_sample_rate(const struct audio_stream *stream)
{
	TRACE_LOG("%s: ", __FUNCTION__);
							 
	return PCM_48K;
}

static int out_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return -ENOSYS;
}

static size_t out_get_buffer_size(const struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return BUFFER_OUT_SIZE;
}

static uint32_t out_get_channels(const struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return AUDIO_CHANNEL_OUT_STEREO;
}

static audio_format_t out_get_format(const struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return AUDIO_FORMAT_PCM_16_BIT;
}

static int out_set_format(struct audio_stream *stream, audio_format_t format)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return -ENOSYS;
}

static int out_standby(struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;
}

static int out_dump(const struct audio_stream *stream, int fd)
{
    TRACE_LOG("%s ", __FUNCTION__);
    return 0;
}

static int out_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;
}

static char * out_get_parameters(const struct audio_stream *stream, const char *keys)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return strdup("");
}

static uint32_t out_get_latency(const struct audio_stream_out *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;
}

static int out_set_volume(struct audio_stream_out *stream, float left,
                          float right)
{
    TRACE_LOG("%s ", __FUNCTION__);
    /* volume controlled in audioflinger mixer (digital) */
    return -ENOSYS;
}

static ssize_t out_write(struct audio_stream_out *stream, const void* buffer, size_t bytes)
{
						  
	TRACE_LOG("%s: ", __FUNCTION__);
						  
	// TODO: Very important API to get decoder raw data
	// use customer codec API here!!!
						  			  
	return bytes;
}


static int out_get_render_position(const struct audio_stream_out *stream,
                                   uint32_t *dsp_frames)
{
    TRACE_LOG("%s ", __FUNCTION__);
    return -EINVAL;
}

static int out_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    TRACE_LOG("%s ", __FUNCTION__);
    return 0;
}

static int out_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
    TRACE_LOG("%s ", __FUNCTION__);
    return 0;
}

static int out_get_next_write_timestamp(const struct audio_stream_out *stream __unused, int64_t *timestamp __unused)
{
	TRACE_LOG("%s ", __FUNCTION__);
	
    return -EINVAL;
}

/*
 * AUDIO INPUT STREAM
 */

static uint32_t in_get_sample_rate(const struct audio_stream *stream)
{
    FNLOG();
	
    return PCM_16K;
}

static int in_set_sample_rate(struct audio_stream *stream, uint32_t rate)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return -ENOSYS;

}

static size_t in_get_buffer_size(const struct audio_stream *stream)
{
    TRACE_LOG("%s ", __FUNCTION__);
	
    return 320;
}

static uint32_t in_get_channels(const struct audio_stream *stream)
{
    TRACE_LOG("%s ", __FUNCTION__);
	
    return AUDIO_CHANNEL_IN_MONO;
}

static audio_format_t in_get_format(const struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return AUDIO_FORMAT_PCM_16_BIT;
}

static int in_set_format(struct audio_stream *stream, audio_format_t format)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return -ENOSYS;

}

static int in_standby(struct audio_stream *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;

}

static int in_dump(const struct audio_stream *stream, int fd)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;
}

static int in_set_parameters(struct audio_stream *stream, const char *kvpairs)
{
    FNLOG();
    return 0;
}

static char * in_get_parameters(const struct audio_stream *stream,
                                const char *keys)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return strdup("");

}

static int in_set_gain(struct audio_stream_in *stream, float gain)
{
	TRACE_LOG("%s ", __FUNCTION__);
									
	return 0;
}

static ssize_t in_read(struct audio_stream_in *stream, void* buffer,
                       size_t bytes)
{
    TRACE_LOG("%s ", __FUNCTION__);
	//TODO: very important API to call your own codec to get decoded raw data.
	
    return bytes;
}

static uint32_t in_get_input_frames_lost(struct audio_stream_in *stream)
{
	TRACE_LOG("%s ", __FUNCTION__);
						   
	return 0;

}

static int in_add_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;

}

static int in_remove_audio_effect(const struct audio_stream *stream, effect_handle_t effect)
{
	TRACE_LOG("%s ", __FUNCTION__);

    return 0;

}



static int adev_open_output_stream(struct audio_hw_device *dev,
                                   audio_io_handle_t handle,
                                   audio_devices_t devices,
                                   audio_output_flags_t flags,
                                   struct audio_config *config,
                                   struct audio_stream_out **stream_out)

{
    ALOGV("adev_open_output_stream...");

    struct stub_audio_device *ladev = (struct stub_audio_device *)dev;
    struct stub_stream_out *out;
    int ret;

    out = (struct stub_stream_out *)calloc(1, sizeof(struct stub_stream_out));
    if (!out)
        return -ENOMEM;

    out->stream.common.get_sample_rate = out_get_sample_rate;
    out->stream.common.set_sample_rate = out_set_sample_rate;
    out->stream.common.get_buffer_size = out_get_buffer_size;
    out->stream.common.get_channels = out_get_channels;
    out->stream.common.get_format = out_get_format;
    out->stream.common.set_format = out_set_format;
    out->stream.common.standby = out_standby;
    out->stream.common.dump = out_dump;
    out->stream.common.set_parameters = out_set_parameters;
    out->stream.common.get_parameters = out_get_parameters;
    out->stream.common.add_audio_effect = out_add_audio_effect;
    out->stream.common.remove_audio_effect = out_remove_audio_effect;
    out->stream.get_latency = out_get_latency;
    out->stream.set_volume = out_set_volume;
    out->stream.write = out_write;
    out->stream.get_render_position = out_get_render_position;
    out->stream.get_next_write_timestamp = out_get_next_write_timestamp;

    *stream_out = &out->stream;
    return 0;

err_open:
    free(out);
    *stream_out = NULL;
    return ret;





}

static void adev_close_output_stream(struct audio_hw_device *dev,
                                     struct audio_stream_out *stream)
{
	ALOGV("adev_close_output_stream...");
	free(stream);
}

static int adev_set_parameters(struct audio_hw_device *dev, const char *kvpairs)
{
	ALOGV("adev_set_parameters");
	return -ENOSYS;
}

static char * adev_get_parameters(const struct audio_hw_device *dev,
                                  const char *keys)
{
    ALOGV("adev_get_parameters");
    return strdup("");
}

static int adev_init_check(const struct audio_hw_device *dev)
{
	ALOGV("adev_init_check");
	return 0;
}

static int adev_set_voice_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_voice_volume: %f", volume);
    return -ENOSYS;
}

static int adev_set_master_volume(struct audio_hw_device *dev, float volume)
{
    ALOGV("adev_set_master_volume: %f", volume);
    return -ENOSYS;
}

static int adev_get_master_volume(struct audio_hw_device *dev, int mode)
{
    ALOGV("adev_get_master_volume: %f", *volume);
    return -ENOSYS;
}

static int adev_set_master_mute(struct audio_hw_device *dev, int mode)
{
    ALOGV("adev_set_master_mute: %d", muted);
    return -ENOSYS;

}

static int adev_get_master_mute(struct audio_hw_device *dev, int mode)
{
    ALOGV("adev_get_master_mute: %d", *muted);
    return -ENOSYS;

}

static int adev_set_mode(struct audio_hw_device *dev, int mode)
{
    ALOGV("adev_set_mode: %d", mode);
    return 0;

}

static int adev_set_mic_mute(struct audio_hw_device *dev, bool state)
{
    ALOGV("adev_set_mic_mute");
    return -ENOSYS;

}

static int adev_get_mic_mute(const struct audio_hw_device *dev, bool *state)
{
    ALOGV("adev_get_mic_mute");
    return -ENOSYS;

}

static size_t adev_get_input_buffer_size(const struct audio_hw_device *dev,
                                         const struct audio_config *config)
{
	ALOGV("adev_get_input_buffer_size: %d", 320);
    return 320;
}

static int adev_open_input_stream(struct audio_hw_device *dev,
                                  audio_io_handle_t handle,
                                  audio_devices_t devices,
                                  struct audio_config *config,
                                  struct audio_stream_in **stream_in)
{
	ALOGV("adev_open_input_stream...");

    struct stub_audio_device *ladev = (struct a2dp_audio_device *)dev;
    struct stub_stream_in *in;
    int ret;

	TRACE_LOG("%s ", __FUNCTION__);
    ALOGI("mic open");   //when box/TV get voice key value, and call audio flinger

    in = (struct stub_stream_in *)calloc(1, sizeof(struct stub_stream_in));

    if (!in)
        return -ENOMEM;

    in->stream.common.get_sample_rate = in_get_sample_rate;
    in->stream.common.set_sample_rate = in_set_sample_rate;
    in->stream.common.get_buffer_size = in_get_buffer_size;
    in->stream.common.get_channels = in_get_channels;
    in->stream.common.get_format = in_get_format;
    in->stream.common.set_format = in_set_format;
    in->stream.common.standby = in_standby;
    in->stream.common.dump = in_dump;
    in->stream.common.set_parameters = in_set_parameters;
    in->stream.common.get_parameters = in_get_parameters;
    in->stream.common.add_audio_effect = in_add_audio_effect;
    in->stream.common.remove_audio_effect = in_remove_audio_effect;
    in->stream.set_gain = in_set_gain;
    in->stream.read = in_read;
    in->stream.get_input_frames_lost = in_get_input_frames_lost;

    *stream_in = &in->stream;
    return 0;

err_open:
    free(in);
    *stream_in = NULL;
    return ret;
}

static void adev_close_input_stream(struct audio_hw_device *dev,
                                   struct audio_stream_in *in)
{
	ALOGV("adev_close_input_stream...");
	return;

}

static int adev_dump(const audio_hw_device_t *device, int fd)
{
	ALOGV("adev_dump");
	return 0;

}

static int adev_close(hw_device_t *device)
{
    ALOGV("adev_close");
    free(device);
    return 0;
}

static int adev_open(const hw_module_t* module, const char* name, hw_device_t** device)
{
	ALOGV("adev_open: %s", name);
	
    struct stub_audio_device *adev;
    int ret;

	TRACE_LOG("%s ", __FUNCTION__);
	ALOGI("Audio device open ...");
	
    if (strcmp(name, AUDIO_HARDWARE_INTERFACE) != 0)
    {
        ERROR("interface %s not matching [%s]", name, AUDIO_HARDWARE_INTERFACE);
        return -EINVAL;
    }

    adev = calloc(1, sizeof(struct stub_audio_device));

    if (!adev)
        return -ENOMEM;

    adev->device.common.tag = HARDWARE_DEVICE_TAG;
    adev->device.common.version = AUDIO_DEVICE_API_VERSION_CURRENT;
    adev->device.common.module = (struct hw_module_t *) module;
    adev->device.common.close = adev_close;

    adev->device.init_check = adev_init_check;
    adev->device.set_voice_volume = adev_set_voice_volume;
    adev->device.set_master_volume = adev_set_master_volume;
	adev->device.get_master_volume = adev_get_master_volume;
    adev->device.set_master_mute = adev_set_master_mute;
    adev->device.get_master_mute = adev_get_master_mute;
    adev->device.set_mode = adev_set_mode;
    adev->device.set_mic_mute = adev_set_mic_mute;
    adev->device.get_mic_mute = adev_get_mic_mute;
    adev->device.set_parameters = adev_set_parameters;
    adev->device.get_parameters = adev_get_parameters;
    adev->device.get_input_buffer_size = adev_get_input_buffer_size;
    adev->device.open_output_stream = adev_open_output_stream;
    adev->device.close_output_stream = adev_close_output_stream;
    adev->device.open_input_stream = adev_open_input_stream;
    adev->device.close_input_stream = adev_close_input_stream;
    adev->device.dump = adev_dump;

    *device = &adev->device.common;

    return 0;
}

static struct hw_module_methods_t hal_module_methods = {
    .open = adev_open,
};

struct audio_module HAL_MODULE_INFO_SYM = {
    .common = {
        .tag = HARDWARE_MODULE_TAG,
        .version_major = 1,
        .version_minor = 0,
        .id = AUDIO_HARDWARE_MODULE_ID,
        .name = "Simon's Audio HW HAL",
        .author = "The Android Open Source Project",
        .methods = &hal_module_methods,
    },
};

