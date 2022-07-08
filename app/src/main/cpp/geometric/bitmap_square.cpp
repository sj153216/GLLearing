//
// Created by SJHCN on 2022/7/7.
//

#include <util/LogUtil.h>
#include "bitmap_square.h"

BitmapSquare *BitmapSquare::instance = nullptr;


BitmapSquare::BitmapSquare() {

}

BitmapSquare::BitmapSquare(GLchar *shader_code, GLchar *fragment_code) {

}

void BitmapSquare::init() {
    program = GLUtil::Create_program(vertexCode, fragmentCode, vertexShader, fragmentShader);
    if (program == 0) {
        return;
    }
    glUseProgram(program);

    if (texture_id == 0) {
        // 生成纹理id
        glGenTextures(1, &texture_id);
    }
    LOGD("texture_id: %d", texture_id);
    LOGD("img_data: %s", img_data);


    glActiveTexture(texture_id);
    glBindTexture(GL_TEXTURE_2D, texture_id);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    if (img_data != nullptr) {
        LOGD("bind");

        glTexImage2D(GL_TEXTURE_2D, 0, // level一般为0
                     GL_RGBA, //纹理内部格式
                     720, 1600, // 画面宽高
                     0, // 必须为0
                     GL_RGBA, // 数据格式，必须和上面的纹理格式保持一直
                     GL_UNSIGNED_BYTE, // RGBA每位数据的字节数，这里是BYTE​: 1 byte
                     img_data);// 画面数据
    }

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


    LOGD("program: %d", program);

//    // 顶点
//    int position = glGetAttribLocation(program, "vPosition");
//    LOGD("position: %d", position);
//
//    glEnableVertexAttribArray(position);
//    glVertexAttribPointer(position, COORDS_PER_VERTEX, GL_FLOAT, GL_FALSE, 0,
//                          vertex_coordinate);
//
//    // 纹理顶点
//    int texture_position = glGetAttribLocation(program, "inputTextureCoordinate");
//    LOGD("texture_position: %d", texture_position);
//
//    glEnableVertexAttribArray(texture_position);
//    glVertexAttribPointer(texture_position, COORDS_PER_TEXTURE_VERTEX, GL_FLOAT, GL_FALSE,
//                          0,
//                          tex_vertex);
//
//
//    glDrawElements(GL_TRIANGLE_STRIP, 6, GL_UNSIGNED_INT, 0);
//    glDrawArrays(GL_TRIANGLE_STRIP, 0, 3);


    float vertices[] = {
            0.5f,  0.5f, 0.0f,  // top right
            0.5f, -0.5f, 0.0f,  // bottom right
            -0.5f, -0.5f, 0.0f,  // bottom left
            -0.5f,  0.5f, 0.0f   // top left
    };
    unsigned int indices[] = {  // note that we start from 0!
            0, 1, 3,  // first Triangle
            1, 2, 3   // second Triangle
    };
    unsigned int VBO, VAO, EBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    int position = glGetAttribLocation(program, "vPosition");
    LOGD("position: %d", position);
    glVertexAttribPointer(position, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(position);


    int texture_position = glGetAttribLocation(program, "inputTextureCoordinate");
    LOGD("texture_position: %d", texture_position);

    glVertexAttribPointer(texture_position, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(texture_position);

//    glBindBuffer(GL_ARRAY_BUFFER, 0);
//    glBindVertexArray(0);

//    glBindVertexArray(VAO);
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);



}

void BitmapSquare::set_image(unsigned char *data, unsigned int img_width, unsigned int img_height) {
    this->img_data = data;
    this->width = img_width;
    this->height = img_height;
}
