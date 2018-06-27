#include  <stdio.h>
#include <jni.h>


jstring  c_print(JNIEnv  * env,jobject  obj,jstring string)
{

	const jbyte *str;
	str = (*env)->GetStringUTFChars(env, string, NULL);
	if (str == NULL) {
		return NULL; /* OutOfMemoryError already thrown */
	}
	printf("%s", str);
	(*env)->ReleaseStringUTFChars(env, string, str);
	return  (*env)->NewStringUTF(env, "farsight");

}


JNINativeMethod  methods [] = {

	{"print","(Ljava/lang/String;)Ljava/lang/String;",(void  *)c_print},
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
