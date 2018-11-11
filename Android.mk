LOCAL_PATH:= $(call my-dir)

include $(CLEAR_VARS)

LOCAL_SRC_FILES:= \
	audio_simon_hw.c

LOCAL_C_INCLUDES+= .

LOCAL_SHARED_LIBRARIES := \
	libcutils liblog

LOCAL_LDFLAGS += -ldl
	
LOCAL_SHARED_LIBRARIES += \
	libpower

LOCAL_MODULE := audio.simon.default
LOCAL_MODULE_PATH := $(TARGET_OUT_SHARED_LIBRARIES)/hw

LOCAL_MODULE_TAGS := optional

include $(BUILD_SHARED_LIBRARY)
