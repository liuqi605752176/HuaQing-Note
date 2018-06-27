#include  <stdio.h>
#include <jni.h>


jint  c_print()
{

	printf("hello world \n");

}


JNINativeMethod  methods [] = {

	{"print","()I",(void  *)c_print},
	{},


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
	(*env)->RegisterNatives(env, cls,methods, 1);
	return JNI_VERSION_1_2;
}
