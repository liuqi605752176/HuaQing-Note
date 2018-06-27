LOCAL_PATH := $(call my-dir)
include $(CLEAR_VARS)
LOCAL_MODULE  := libjninative 
LOCAL_SRC_FILES  :=src/hello.c 
LOCAL_SHARED_LIBRARIES  +=liblog  libhardware
LOCAL_MODULE_PATH :=$(LOCAL_PATH)/lib
include $(BUILD_SHARED_LIBRARY)
