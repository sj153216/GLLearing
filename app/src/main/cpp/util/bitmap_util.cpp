//
// Created by SJHCN on 2022/7/7.
//

#include <android/bitmap.h>
#include <cstdlib>
#include "bitmap_util.h"
#include "LogUtil.h"


void BitmapUtil::processBitmap(JNIEnv *env, jobject jbitmap, unsigned char **resultData, unsigned int *width, unsigned int *height) {

    if (jbitmap == nullptr) {
        return;
    }

    // 获取图片信息
    AndroidBitmapInfo info;
    int result;
    result = AndroidBitmap_getInfo(env, jbitmap, &info);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_getInfo failed, result: %d", result);
        return;
    }

    LOGD("bitmap width: %d, height: %d, format: %d, stride: %d", info.width, info.height,
         info.format, info.stride);

    // 获取像素信息
    unsigned char *addrPtr;
    result = AndroidBitmap_lockPixels(env, jbitmap, reinterpret_cast<void **>(&addrPtr));
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_lockPixels failed, result: %d", result);
        return;
    }


    // 执行图片操作的逻辑
    size_t length = info.stride * info.height;
    LOGD("length: %zu", length);

    *resultData = static_cast<unsigned char *>(malloc(length * sizeof(unsigned char)));
    memcpy(*resultData, addrPtr, length);


    // 像素信息不再使用后需要解除锁定
    result = AndroidBitmap_unlockPixels(env, jbitmap);
    if (result != ANDROID_BITMAP_RESULT_SUCCESS) {
        LOGE("AndroidBitmap_unlockPixels failed, result: %d", result);
    }

}
