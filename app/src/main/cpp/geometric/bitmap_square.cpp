//
// Created by SJHCN on 2022/7/7.
//

#include <util/LogUtil.h>
#include "bitmap_square.h"
#include "glm_util.h"

BitmapSquare *BitmapSquare::instance = nullptr;


BitmapSquare::BitmapSquare() {

}

BitmapSquare::BitmapSquare(GLchar *shader_code, GLchar *fragment_code) {

}

void BitmapSquare::init() {
    program = GLUtil::Create_program(vertexCode, fragmentCode, vertexShader, fragmentShader);
    sample2D = glGetUniformLocation(program, "inputImageTexture");
//    if (program == 0) {
//        return;
//    }
//    glUseProgram(program);
//
    if (texture_id == 0) {
        // 生成纹理id
        glGenTextures(1, &texture_id);
    }

    glBindTexture(GL_TEXTURE_2D, texture_id);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

}

void BitmapSquare::setShaderCode(const GLchar *vertexCode, const GLchar *fragmentCode) {
    this->vertexCode = vertexCode;
    this->fragmentCode = fragmentCode;
}

BitmapSquare::~BitmapSquare() {

    if (program) {
        glDeleteProgram(program);
    }

    if (vertexCode) {
        vertexCode = nullptr;
    }
    if (fragmentCode) {
        fragmentCode = nullptr;
    }

}

void BitmapSquare::setTextureId(GLint textureId) {
    this->texture_id = textureId;
}

BitmapSquare *BitmapSquare::Get_instance() {

    if (instance == nullptr) {
        LOGD("first");

        instance = new BitmapSquare();
        return instance;
    }
    return instance;
}

void BitmapSquare::draw() {
    if (program == 0) {
        return;
    }
    glUseProgram(program);


    GLfloat verticesCoords[] = {
            -1.0f,  0.5f, 0.0f,  // Position 0
            -1.0f, -0.5f, 0.0f,  // Position 1
            1.0f, -0.5f, 0.0f,  // Position 2
            1.0f,  0.5f, 0.0f,  // Position 3
    };

    GLfloat textureCoords[] = {
            0.0f,  0.0f,        // TexCoord 0
            0.0f,  1.0f,        // TexCoord 1
            1.0f,  1.0f,        // TexCoord 2
            1.0f,  0.0f         // TexCoord 3
    };

    GLushort indices[] = { 0, 1, 2, 0, 2, 3 };

    //upload RGBA image data
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);
    LOGD("last img: %zu", strlen(reinterpret_cast<const char *const>(img_data)));
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, img_data);
    glBindTexture(GL_TEXTURE_2D, GL_NONE);

    // Use the program object
    glUseProgram (program);

    // Load the vertex position
    glVertexAttribPointer (0, 3, GL_FLOAT,
                           GL_FALSE, 3 * sizeof (GLfloat), verticesCoords);
    // Load the texture coordinate
    glVertexAttribPointer (1, 2, GL_FLOAT,
                           GL_FALSE, 2 * sizeof (GLfloat), textureCoords);

    glEnableVertexAttribArray (0);
    glEnableVertexAttribArray (1);

    // Bind the RGBA map
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id);



    // Set the RGBA map sampler to texture unit to 0
    glUniform1i(sample2D, 0);

    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_SHORT, indices);



}

void BitmapSquare::set_image(unsigned char *data, unsigned int img_width, unsigned int img_height) {
    this->img_data = data;
    this->width = img_width;
    this->height = img_height;
}

void BitmapSquare::set_path(unsigned char *path) {
    this->file_path = path;

}
