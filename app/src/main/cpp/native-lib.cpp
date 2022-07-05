#include <jni.h>
#include <string>
#include "Triangle.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeInit(JNIEnv *env, jobject thiz) {
    Triangle triangle;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnSurfaceCreated(JNIEnv *env, jobject thiz) {
    Triangle triangle;

}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnSurfaceChanged(JNIEnv *env, jobject thiz) {
}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnDrawFrame(JNIEnv *env, jobject thiz) {
}