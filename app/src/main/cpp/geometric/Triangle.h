//
// Created by SJHCN on 2022/7/5.
//

#ifndef GLLEARNING_TRIANGLE_H
#define GLLEARNING_TRIANGLE_H

#include "../glm_util.h"
#include <GLES3/gl3.h>
#include "util/gl_util.h"


// 三角形绘制类
class Triangle {

private:

    static Triangle *instance;
    const int COORDS_PER_VERTEX = 3; // 每个顶点的坐标数
    // 顶点坐标
    GLfloat vertex_coordinate[9] = {
            0.0f, 0.5f, 0.0f,
            -0.5f, 0.0f, 0.0f,
            0.5f, 0.0f, 0.0f
    };

    int program; // 着色器程序ID引用
    int vertexCount =
            sizeof(vertex_coordinate) / sizeof(vertex_coordinate[0]) / COORDS_PER_VERTEX; // 顶点数量
    int vertexStride = COORDS_PER_VERTEX * 4; // 顶点之间的步长

    const GLchar *vertexCode = 0; // 顶点着色器代码
    const GLchar *fragmentCode = 0; // 片段着色器代码
    GLuint vertexShader; // 顶点着色器句柄
    GLuint fragmentShader; // 片段着色器句柄



public:
    Triangle(GLchar *shader_code, GLchar *fragment_code);

    Triangle();

    void init();

    void draw(); // 绘制

    void setShaderCode(const GLchar *vertexCode, const GLchar *fragmentCode);

    ~Triangle();

    static Triangle *Get_instance();

};


#endif //GLLEARNING_TRIANGLE_H
