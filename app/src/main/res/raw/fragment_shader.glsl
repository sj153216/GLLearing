#version 300 es
precision mediump float;
in vec2 textureCoordinate;
layout(location = 0) out vec4 outColor;
uniform sampler2D inputImageTexture;
void main(){
    outColor = texture(inputImageTexture, textureCoordinate);
}
