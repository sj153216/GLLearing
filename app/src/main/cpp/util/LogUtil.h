//
// Created by SJHCN on 2022/7/5.
//

#ifndef GLLEARNING_LOGUTIL_H
#define GLLEARNING_LOGUTIL_H


#include <android/log.h>
#include <string.h>

#define LOG_TAG "learning-gl"

#define LOGI(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)
#define LOGE(...)  __android_log_print(ANDROID_LOG_ERROR, LOG_TAG, __VA_ARGS__)
#define LOGD(...)  __android_log_print(ANDROID_LOG_INFO, LOG_TAG, __VA_ARGS__)

#endif //GLLEARNING_LOGUTIL_H
