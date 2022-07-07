#include <jni.h>
#include <string>
#include <util/LogUtil.h>
#include "geometric/Triangle.h"

extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeInit(JNIEnv *env, jobject thiz) {

}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnSurfaceCreated(JNIEnv *env, jobject thiz,
                                                          jstring vertexCode,
                                                          jstring fragmentCode) {

    jboolean copy = false;
    const char *vertex_code = env->GetStringUTFChars(vertexCode, &copy);
    const char *fragment_code = env->GetStringUTFChars(fragmentCode, &copy);
//    LOGD("vertex code: %s", vertex_code);
//    LOGD("fragment code: %s", fragment_code);
    Triangle *instance = Triangle::Get_instance();
    instance->setShaderCode(vertex_code, fragment_code);
    instance->init();

}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnSurfaceChanged(JNIEnv *env, jobject thiz) {
}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_nativeOnDrawFrame(JNIEnv *env, jobject thiz) {
    LOGD("nativeOnDrawFrame");

    Triangle::Get_instance()->draw();

}