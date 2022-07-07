//
// Created by SJHCN on 2022/7/5.
//
#include "Triangle.h"
#include "../util/LogUtil.h"

Triangle *Triangle::instance = nullptr;

Triangle::Triangle(GLchar *vertex_code, GLchar *fragment_code) {

    vertexCode = vertex_code;
    fragmentCode = fragment_code;

    program = GLUtil::Create_program(vertexCode, fragmentCode, vertexShader, fragmentShader);
}

Triangle::Triangle() {

}

Triangle::~Triangle() {

    if (program) {
        glDeleteProgram(program);
    }

}

void Triangle::draw() {
    if (program == 0) {
        return;
    }
    glUseProgram(program);

    int position = glGetAttribLocation(program, "vPosition");
    glVertexAttribPointer(position, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, vertexStride,
                          vertex_coordinate);
    glEnableVertexAttribArray(0);

    glDrawArrays(GL_TRIANGLES, 0, vertexCount);
}

Triangle *Triangle::Get_instance() {
    if (instance == nullptr) {
        instance = new Triangle;
        return instance;
    }

    return instance;
}

void Triangle::setShaderCode(const GLchar *vertexCode, const GLchar *fragmentCode) {
    this->vertexCode = vertexCode;
    this->fragmentCode = fragmentCode;
}

void Triangle::init() {
    program = GLUtil::Create_program(vertexCode, fragmentCode, vertexShader, fragmentShader);
}
