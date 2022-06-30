//#extension GL_OES_EGL_image_external : require
//precision mediump float;
//varying vec2 textureCoordinate;
//uniform samplerExternalOES s_texture;
//const float offset = 1.0f / 300.0f;
//
//
//void main() {
//
//    /** 反相 **/
//    /*gl_FragColor = vec4(vec3(1.0 - texture2D(s_texture, textureCoordinate)), 1.0);*/
//
//    // 核效果取周围像素值的偏移量
//    vec2 offsets[9];
//    offsets[0] = vec2(-offset, offset);// 左上
//    offsets[1] = vec2(0.0f, offset);// 正上
//    offsets[2] = vec2(offset, offset);// 右上
//    offsets[3] = vec2(-offset, 0.0f);// 左
//    offsets[4] = vec2(0.0f, 0.0f);// 中
//    offsets[5] = vec2(offset, 0.0f);// 右
//    offsets[6] = vec2(-offset, -offset);// 左下
//    offsets[7] = vec2(0.0f, -offset);// 正下
//    offsets[8] = vec2(offset, -offset);// 右下
//    // 核函数
//    float kernel[9];
//    kernel[0] = 1.0f;
//    kernel[1] = 1.0f;
//    kernel[2] = 1.0f;
//    kernel[3] = 1.0f;
//    kernel[4] = -8.0f;
//    kernel[5] = 1.0f;
//    kernel[6] = 1.0f;
//    kernel[7] = 1.0f;
//    kernel[8] = 1.0f;
//    // 计算采样值
//    vec3 sampleTex[9];
//    for (int i = 0; i < 9; i++)
//    {
//        sampleTex[i] = vec3(texture2D(s_texture, textureCoordinate.xy + offsets[i]));
//    }
//    vec3 col = vec3(0.0);
//    for (int i = 0; i < 9; i++)
//    col += sampleTex[i] * kernel[i];
//
//    gl_FragColor = vec4(col, 1.0);
//
//
//}


//素描图像处理的渲染器
#extension GL_OES_EGL_image_external : require
precision mediump float;
varying vec2 textureCoordinate;
uniform samplerExternalOES s_texture;

void main() {
    vec4 curColor = texture2D(s_texture,textureCoordinate);
    //1、去色（黑白化）
    float h = 0.299*curColor.x + 0.587*curColor.y + 0.114*curColor.z;
    vec4 fanshe = vec4(h,h,h,0.0);

    //2、获取该纹理附近的上下左右的纹理并求其去色，补色
    vec4 sample0,sample1,sample2,sample3;
    float h0,h1,h2,h3;
    float fstep=0.0015;
    sample0=texture2D(s_texture,vec2(textureCoordinate.x-fstep,textureCoordinate.y-fstep));
    sample1=texture2D(s_texture,vec2(textureCoordinate.x+fstep,textureCoordinate.y-fstep));
    sample2=texture2D(s_texture,vec2(textureCoordinate.x+fstep,textureCoordinate.y+fstep));
    sample3=texture2D(s_texture,vec2(textureCoordinate.x-fstep,textureCoordinate.y+fstep));
    //这附近的4个纹理值同样得进行去色（黑白化）
    h0 = 0.299*sample0.x + 0.587*sample0.y + 0.114*sample0.z;
    h1 = 0.299*sample1.x + 0.587*sample1.y + 0.114*sample1.z;
    h2 = 0.299*sample2.x + 0.587*sample2.y + 0.114*sample2.z;
    h3 = 0.299*sample3.x + 0.587*sample3.y + 0.114*sample3.z;
    //反相，得到每个像素的补色
    sample0 = vec4(1.0-h0,1.0-h0,1.0-h0,0.0);
    sample1 = vec4(1.0-h1,1.0-h1,1.0-h1,0.0);
    sample2 = vec4(1.0-h2,1.0-h2,1.0-h2,0.0);
    sample3 = vec4(1.0-h3,1.0-h3,1.0-h3,0.0);
    //3、对反相颜色值进行均值模糊
    vec4 color=(sample0+sample1+sample2+sample3) / 4.0;
    //4、颜色减淡，将第1步中的像素和第3步得到的像素值进行计算
    vec3 endColor = fanshe.rgb+(fanshe.rgb*color.rgb)/(1.0-color.rgb);
    //最终获取的颜色
    gl_FragColor = vec4(endColor,0.0);
}