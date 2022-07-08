#include <jni.h>
#include <string>
#include <util/LogUtil.h>
#include <util/bitmap_util.h>
#include <geometric/bitmap_square.h>
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
//    Triangle *instance = Triangle::Get_instance();
//    instance->setShaderCode(vertex_code, fragment_code);
//    instance->init();
    BitmapSquare *instance = BitmapSquare::Get_instance();
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

//    Triangle::Get_instance()->draw();
    BitmapSquare::Get_instance()->draw();

}
extern "C"
JNIEXPORT void JNICALL
Java_com_three_gllearning_MyRender_native_1texImage2D(JNIEnv *env, jobject thiz, jobject bitmap) {

    unsigned char *resultData;
    unsigned int width;
    unsigned int height;
    BitmapUtil bitmapUtil;
    bitmapUtil.processBitmap(env ,bitmap, &resultData, &width, &height);
    LOGD("processBitmap: %s", resultData);

    BitmapSquare::Get_instance()->set_image(resultData, width, height);
}