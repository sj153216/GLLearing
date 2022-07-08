//
// Created by SJHCN on 2022/7/7.
//

#ifndef GLLEARNING_BITMAP_SQUARE_H
#define GLLEARNING_BITMAP_SQUARE_H

#include "util/gl_util.h"
#include <android/bitmap.h>


class BitmapSquare{
private:

    static BitmapSquare *instance;
    const int COORDS_PER_VERTEX = 3; // 每个顶点的坐标数
    const int COORDS_PER_TEXTURE_VERTEX = 2; // 每个纹理顶点的坐标数
    // 顶点坐标
    GLfloat vertex_coordinate[12] = {
            -0.5f, 0.5f, 0.0f,      // top left
            -0.5f, -0.5f, 0.0f,      // bottom left
            0.5f, -0.5f, 0.0f,      // bottom right
            0.5f, 0.5f, 0.0f       // top right
    };

    // 顶点对应的纹理坐标
    GLfloat tex_vertex[8] = {
            0.0f, 0.0f,      // top left
            0.0f, 1.0f,      // bottom left
            1.0f, 1.0f,       // bottom right
            1.0f, 0.0f     // top right
    };

    // 绘制顺序
    GLshort draw_order[6] = {0, 1, 2, 0, 2, 3};
    // 纹理id
    GLuint texture_id = 0;

    int program; // 着色器程序ID引用
    GLint sample2D;
    int vertexCount =
            sizeof(vertex_coordinate) / sizeof(vertex_coordinate[0]) / COORDS_PER_VERTEX; // 顶点数量
    int vertexStride = COORDS_PER_VERTEX * 4; // 顶点之间的步长
    int vertexTextureStride = COORDS_PER_TEXTURE_VERTEX * 4; // 顶点之间的步长

    const GLchar *vertexCode = 0; // 顶点着色器代码
    const GLchar *fragmentCode = 0; // 片段着色器代码
    GLuint vertexShader; // 顶点着色器句柄
    GLuint fragmentShader; // 片段着色器句柄

    unsigned char *img_data = nullptr;
    unsigned int width;
    unsigned int height;



public:
    BitmapSquare(GLchar *shader_code, GLchar *fragment_code);

    BitmapSquare();

    void init();

    void draw(); // 绘制

    void setShaderCode(const GLchar *vertexCode, const GLchar *fragmentCode);

    ~BitmapSquare();

    void setTextureId(GLint textureId);

    void set_image(unsigned char *data, unsigned int width, unsigned int height);



    static BitmapSquare *Get_instance();

};

#endif //GLLEARNING_BITMAP_SQUARE_H
