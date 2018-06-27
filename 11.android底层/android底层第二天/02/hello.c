#include  <stdio.h>
#include <jni.h>


jint  c_print(JNIEnv  * env,jobject  obj)
{

	printf("hello world \n");

}
jint c_open(JNIEnv  * env,jobject  obj)
{

	printf("c_open  \n");

}
jint  c_read(JNIEnv  *env,jobject  obj)
{

	printf("c_read \n");
}
jint  c_write(JNIEnv *env,jobject obj,jint val)
{

	printf("c_write = %d\n",val);
	return  380;

}
jint  c_ioctl(JNIEnv  * env,jobject  obj,jint which,jint status)
{

	printf("which  = %d,status  = %d\n",which,status);

	return  250;
}


JNINativeMethod  methods [] = {

	{"print","()I",(void  *)c_print},
	{"hello_open","()I",(void *)c_open},
	{"hello_read","()I",(void *)c_read},
	{"hello_write","(I)I",(void *)c_write},
	{"hello_ioctl","(II)I",(void *)c_ioctl},


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
	cls = (*env)->FindClass(env, "hello");
	if (cls == NULL) {
		return JNI_ERR;
	}
	//建立映射 
	(*env)->RegisterNatives(env, cls,methods, sizeof(methods)/sizeof(methods[0]));
	return JNI_VERSION_1_2;
}
