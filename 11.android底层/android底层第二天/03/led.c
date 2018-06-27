#include  <stdio.h>
#include <jni.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>


int fd;

jint  native_led_open(JNIEnv  *  env,jobject  obj)
{

	fd  = open("/dev/led",O_RDWR);
	if(fd  <  0)
	{
	
		perror("file  open   fail  \n");
		return  -1;
	
	}
	
	printf("native_led_open   success \n");
	return  fd;

}
jint native_led_ioctl(JNIEnv  * env,jobject  obj,jint which,jint status)
{

	printf("which  = %d,status  = %d\n",which,status);
	ioctl(fd,which,status);
	return  0;

}


JNINativeMethod  methods [] = {

	{"led_open","()I",(void  *)native_led_open},
	{"led_ioctl","(II)I",(void  *)native_led_ioctl},


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
	cls = (*env)->FindClass(env, "Led");
	if (cls == NULL) {
		return JNI_ERR;
	}
	//建立映射 
	(*env)->RegisterNatives(env, cls,methods, sizeof(methods)/sizeof(methods[0]));
	return JNI_VERSION_1_2;
}
