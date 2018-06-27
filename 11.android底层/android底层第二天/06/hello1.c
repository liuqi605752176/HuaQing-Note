
#include  <jni.h>
/*
 * Class:     hello
 * Method:    print
 * Signature: (Ljava/lang/String;)Ljava/lang/String;
 */
JNIEXPORT jstring JNICALL Java_hello_print
  (JNIEnv *env, jobject  obj, jstring  prompt)
{


	char buf[128];
	const jbyte *str;
	str = (*env)->GetStringUTFChars(env, prompt, NULL);
	if (str == NULL) {
		return NULL; /* OutOfMemoryError already thrown */
	}
	printf("%s", str);
	(*env)->ReleaseStringUTFChars(env, prompt, str);
	/* We assume here that the user does not type more than
	 * * 127 characters */
	return (*env)->NewStringUTF(env, "123456");

}

