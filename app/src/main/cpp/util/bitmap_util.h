//
// Created by SJHCN on 2022/7/7.
//

#ifndef GLLEARNING_BITMAP_UTIL_H
#define GLLEARNING_BITMAP_UTIL_H

class BitmapUtil{
public:
    /**
     * 处理java层传来的bitmap信息
     * @param env
     * @param jbitmap
     */
    void processBitmap(JNIEnv* env, jobject jbitmap, unsigned char **resultData, unsigned int *width, unsigned int *height);

};

#endif //GLLEARNING_BITMAP_UTIL_H
