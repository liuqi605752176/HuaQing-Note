

#define  LOG_TAG  "hello"

#include  <stdio.h>
#include <jni.h>
#include <utils/Log.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <hardware/hardware.h>
#include  "led.h"

struct led_device_t  *led_device;
jint  jninative_open(JNIEnv  *env,jobject  obj)
{

	int err;
	hw_module_t  * module;
	hw_device_t  *device;

	err  = hw_get_module("led",(hw_module_t  const   **)&module);
	if(err  ==  0)
	{
	     err  = module->methods->open(module,NULL,&device);
		 if(err  ==  0)
		 {
		 
			 led_device  =  (struct led_device_t * )device;
			 led_device->hw_open(led_device);
		 
		 }
	
	}
	ALOGI("jninative_open    success \n");
	return  0;

}
jint  jninative_ioctl(JNIEnv  *env,jobject  obj,jint which,jint status)
{


	ALOGI("jninative_ioctl  which  = %d,status  = %d\n",which,status);

	led_device->hw_ioctl(led_device,which,status);
	return  0;

}


JNINativeMethod  methods [] = {

	{"hello_open","()I",(void  *)jninative_open},
	{"hello_ioctl","(II)I",(void  *)jninative_ioctl},


};	
	
	JNIEXPORT jint JNICALL
JNI_OnLoad(JavaVM *jvm, void *reserved)
{
	JNIEnv *env;
	jclass cls;
	//获取java运行环境
	if ((*jvm)->GetEnv(jvm, (void **)&env, JNI_VERSION_1_2)) {
		return JNI_ERR; /* JNI version not supported */
	}

	//寻找java中的类名
	cls = (*env)->FindClass(env, "com/farsight/jninative/jninative");
	if (cls == NULL) {
		return JNI_ERR;
	}
	//建立映射 
	(*env)->RegisterNatives(env, cls,methods, 2);
	return JNI_VERSION_1_2;
}
