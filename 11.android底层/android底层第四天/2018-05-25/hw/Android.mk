LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE  := led.default 
LOCAL_SRC_FILES  :=leds.c
LOCAL_SHARED_LIBRARIES  +=liblog  libhardware
LOCAL_MODULE_PATH :=$(LOCAL_PATH)/lib
include $(BUILD_SHARED_LIBRARY)
