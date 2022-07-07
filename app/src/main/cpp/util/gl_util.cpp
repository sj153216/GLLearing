//
// Created by SJHCN on 2022/7/6.
//'

#include <GLES3/gl3.h>
#include <cstdlib>
#include "gl_util.h"
#include "LogUtil.h"


// 加载 shader
GLint GLUtil::Load_shader(GLenum type, const GLchar *shader_code) {
    GLuint shader = glCreateShader(type);
    if (shader) {
        glShaderSource(shader, 1, &shader_code, nullptr);
        glCompileShader(shader);
        GLint compiled = 0;
        glGetShaderiv(shader, GL_COMPILE_STATUS, &compiled);

        if (!compiled) {
            GLint infoLen = 0;
            glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);
            if (infoLen) {
                char *buf = static_cast<char *>(malloc(infoLen));
                if (buf) {
                    glGetShaderInfoLog(shader, infoLen, nullptr, buf);
                    free(buf);
                }
                glDeleteShader(shader);
                shader = 0;
            }
        }
    }
    return shader;
}

// 创建着色器程序
GLint GLUtil::Create_program(const GLchar *pVertexShaderSource, const GLchar *pFragShaderSource,
                     GLuint &vertexShaderHandle, GLuint &fragShaderHandle) {
    GLuint program = 0;
    vertexShaderHandle = Load_shader(GL_VERTEX_SHADER, pVertexShaderSource);
    if (!vertexShaderHandle) {
        return program;
    }
    fragShaderHandle = Load_shader(GL_FRAGMENT_SHADER, pFragShaderSource);
    if (!fragShaderHandle) {
        return program;
    }

    program = glCreateProgram();
    if (program) {
        glAttachShader(program, vertexShaderHandle);
        glAttachShader(program, fragShaderHandle);
        glLinkProgram(program);

        GLint linkStatus = GL_FALSE;
        glGetProgramiv(program, GL_LINK_STATUS, &linkStatus);

        glDetachShader(program, vertexShaderHandle);
        glDeleteShader(vertexShaderHandle);
        vertexShaderHandle = 0;
        glDetachShader(program, fragShaderHandle);
        glDeleteShader(fragShaderHandle);
        fragShaderHandle = 0;

        if (linkStatus != GL_TRUE) {
            GLint bufLength = 0;
            glGetProgramiv(program, GL_INFO_LOG_LENGTH, &bufLength);
            if (bufLength) {
                char *buf = (char *) malloc((size_t) bufLength);
                if (buf) {
                    glGetProgramInfoLog(program, bufLength, nullptr, buf);
                    free(buf);
                }
            }
            glDeleteProgram(program);
            program = 0;
        }
    }
    return program;
}

// 删除 program
void GLUtil::Delete_program(GLuint &program) {
    if (program) {
        glUseProgram(0);
        glDeleteProgram(program);
        program = 0;
    }
}
