#include <jni.h>
#include "testlib.h"

extern "C"
JNIEXPORT jdouble JNICALL
Java_com_testlib_TestlibModule_nativeMultiply(JNIEnv *env, jclass type, jdouble a, jdouble b) {
    return testlib::multiply(a, b);
}
