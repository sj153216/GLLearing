//
// Created by SJHCN on 2022/7/6.
//

#ifndef GLLEARNING_GL_UTIL_H
#define GLLEARNING_GL_UTIL_H

#include <GLES3/gl3.h>


class GLUtil{
public:
    static GLint Load_shader(GLenum type, const GLchar *shader_code);
    static GLint Create_program(const GLchar *pVertexShaderSource, const GLchar *pFragShaderSource,
                                GLuint &vertexShaderHandle, GLuint &fragShaderHandle);
    static void Delete_program(GLuint &program);
};

#endif //GLLEARNING_GL_UTIL_H
