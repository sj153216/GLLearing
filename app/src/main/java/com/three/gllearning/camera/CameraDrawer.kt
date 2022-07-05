package com.three.gllearning.camera

import android.graphics.SurfaceTexture
import android.opengl.GLES11Ext
import android.opengl.GLES30
import com.three.gllearning.MyApplication
import com.three.gllearning.R
import com.three.gllearning.util.FileLoader
import com.three.gllearning.util.OpenGLUtil
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import java.nio.ShortBuffer

/**
 * @Description: 绘制摄像头数据
 * @ClassName: CameraDrawer
 * @Package: com.three.gllearning.camera
 * @Date: 2022/6/29 18:55
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class CameraDrawer {

    // 着色器程序ID引用
    private var program = 0

    // 四边形顶点的坐标
    private var squareCoords = floatArrayOf(
        -1f, 1f, 0.0f,      // top left
        -1f, -1f, 0.0f,      // bottom left
        1f, -1f, 0.0f,      // bottom right
        1f, 1f, 0.0f       // top right

    )

    // 顶点所对应的纹理坐标，摄像头的纹理跟普通的图片纹理坐标有所区别，相差90度，这里注意一下
    private var textureVertices = floatArrayOf(
        0f, 1f,      // top left
        1f, 1f,      // bottom left
        1f, 0f,       // bottom right
        0f, 0f     // top right

    )

    // 相机预览SurfaceTexture
    private var cameraSurfaceTexture: SurfaceTexture? = null

    // 四个顶点的缓冲数组
    private val vertexBuffer: FloatBuffer =
        ByteBuffer.allocateDirect(squareCoords.size * 4).order(ByteOrder.nativeOrder())
            .asFloatBuffer().apply {
                put(squareCoords)
                position(0)
            }

    // 四个顶点的绘制顺序数组
    private val drawOrder = shortArrayOf(0, 1, 2, 0, 2, 3)

    // 四个顶点绘制顺序数组的缓冲数组
    private val drawListBuffer: ShortBuffer =
        ByteBuffer.allocateDirect(drawOrder.size * 2).order(ByteOrder.nativeOrder())
            .asShortBuffer().apply {
                put(drawOrder)
                position(0)
            }


    // 四个顶点的纹理坐标缓冲数组
    private val textureVerticesBuffer: FloatBuffer =
        ByteBuffer.allocateDirect(textureVertices.size * 4).order(ByteOrder.nativeOrder())
            .asFloatBuffer().apply {
                put(textureVertices)
                position(0)
            }


    private var textureID = 0

    // 每个顶点的坐标数
    private val COORDS_PER_VERTEX = 3

    // 每个纹理顶点的坐标数
    private val COORDS_PER_TEXTURE_VERTEX = 2
    private val vertexStride: Int = COORDS_PER_VERTEX * 4
    private val textVertexStride: Int = COORDS_PER_TEXTURE_VERTEX * 4

    init {
        // 编译顶点着色器和片段着色器
        val vertexShaderCode: String =
            FileLoader.loadShader(R.raw.camera_vertex_shader, MyApplication.get().resources)
        val vertexShader: Int = loadShader(GLES30.GL_VERTEX_SHADER, vertexShaderCode)
        val fragmentShaderCode: String =
            FileLoader.loadShader(R.raw.camera_fragment_shader, MyApplication.get().resources)
        val fragmentShader: Int = loadShader(GLES30.GL_FRAGMENT_SHADER, fragmentShaderCode)

        // glCreateProgram函数创建一个着色器程序，并返回新创建程序对象的ID引用
        program = GLES30.glCreateProgram().also {
            // 把顶点着色器添加到程序对象
            GLES30.glAttachShader(it, vertexShader)
            // 把片段着色器添加到程序对象
            GLES30.glAttachShader(it, fragmentShader)
            // 连接并创建一个可执行的OpenGL ES程序对象
            GLES30.glLinkProgram(it)
        }
        val texture = OpenGLUtil.createTextures(
            GLES11Ext.GL_TEXTURE_EXTERNAL_OES, 1,
            GLES30.GL_NEAREST, GLES30.GL_LINEAR,
            GLES30.GL_CLAMP_TO_EDGE, GLES30.GL_CLAMP_TO_EDGE
        )
        textureID = texture[0]
        cameraSurfaceTexture = SurfaceTexture(textureID)
        GLES30.GL_FLOAT_VEC3
    }

    fun getSurfaceTexture(): SurfaceTexture? {
        return cameraSurfaceTexture
    }

    private fun loadShader(type: Int, shaderCode: String): Int {
        // glCreateShader函数创建一个顶点着色器或者片段着色器,并返回新创建着色器的ID引用
        val shader = GLES30.glCreateShader(type)
        // 把着色器和代码关联,然后编译着色器
        GLES30.glShaderSource(shader, shaderCode)
        GLES30.glCompileShader(shader)
        return shader
    }

    // 绘制
    fun draw() {
        // 激活着色器程序 Add program to OpenGL ES environment
        GLES30.glUseProgram(program)
        // 获取顶点着色器中的vPosition变量(因为之前已经编译过着色器代码,所以可以从着色器程序中获取);用唯一ID表示
        val position = GLES30.glGetAttribLocation(program, "vPosition")
        // 允许操作顶点对象position
        GLES30.glEnableVertexAttribArray(position)
        // 将顶点数据传递给position指向的vPosition变量;将顶点属性与顶点缓冲对象关联
        GLES30.glVertexAttribPointer(
            position, COORDS_PER_VERTEX, GLES30.GL_FLOAT,
            false, vertexStride, vertexBuffer
        )
        // 激活textureID对应的纹理单元
        GLES30.glActiveTexture(textureID)
        // 绑定纹理
        GLES30.glBindTexture(GLES30.GL_TEXTURE_2D, textureID)
        // 获取顶点着色器中的inputTextureCoordinate变量(纹理坐标);用唯一ID表示
        val textureCoordinate = GLES30.glGetAttribLocation(program, "inputTextureCoordinate")
        // 允许操作纹理坐标inputTextureCoordinate变量
        GLES30.glEnableVertexAttribArray(textureCoordinate)
        // 将纹理坐标数据传递给inputTextureCoordinate变量
        GLES30.glVertexAttribPointer(
            textureCoordinate, COORDS_PER_TEXTURE_VERTEX, GLES30.GL_FLOAT,
            false, textVertexStride, textureVerticesBuffer
        )
        // 按drawListBuffer中指定的顺序绘制四边形
        GLES30.glDrawElements(
            GLES30.GL_TRIANGLE_STRIP, drawOrder.size,
            GLES30.GL_UNSIGNED_SHORT, drawListBuffer
        )
        // 操作完后,取消允许操作顶点对象position
        GLES30.glDisableVertexAttribArray(position)
        GLES30.glDisableVertexAttribArray(textureCoordinate)

    }

}