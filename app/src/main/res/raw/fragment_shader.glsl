varying highp vec2 textureCoordinate;
uniform sampler2D inputImageTexture;
precision mediump float;

//uniform vec4 vColor;

void main() {
    // 将2D纹理inputImageTexture和纹理顶点坐标通过texture2D计算后传给片段着色器
    gl_FragColor = texture2D(inputImageTexture, textureCoordinate);
}
