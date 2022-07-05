package com.three.gllearning.geometric

import android.opengl.GLES30
import com.three.gllearning.MyApplication
import com.three.gllearning.R
import com.three.gllearning.util.FileLoader
import java.nio.ByteBuffer
import java.nio.ByteOrder
import java.nio.FloatBuffer
import java.nio.ShortBuffer

/**
 * @Description: 四边形
 * @ClassName: Square
 * @Package: com.three.gllearning.geometric
 * @Date: 2022/6/29 13:48
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class Square {


    // 顶点坐标
    private val vertexCoordinate = floatArrayOf(
        -0.5f, 0.5f, 0.0f,      // top left
        -0.5f, 0f, 0.0f,      // bottom left
        0.5f, 0f, 0.0f,      // bottom right
        0.5f, 0.5f, 0.0f       // top right
    )

    private val vertexCount: Int = vertexCoordinate.size / COORDS_PER_VERTEX
    private val vertexStride: Int = COORDS_PER_VERTEX * 4 // 4 bytes per vertex

    // 顶点缓冲数组
    private val vertexBuffer: FloatBuffer =
        ByteBuffer.allocateDirect(vertexCoordinate.size * 4).order(ByteOrder.nativeOrder())
            .asFloatBuffer().apply {
                put(vertexCoordinate)
                position(0)
            }

    // 四个顶点的绘制顺序数组
    private val drawOrder = shortArrayOf(0, 1, 2, 0, 2, 3)

    // 颜色
    private val color = floatArrayOf(0.6f, 0.7f, 0.2f, 1.0f)

    // 四个顶点绘制顺序数组的缓冲数组
    private val drawListBuffer: ShortBuffer =
        ByteBuffer.allocateDirect(drawOrder.size * 2).order(ByteOrder.nativeOrder())
            .asShortBuffer().apply {
                put(drawOrder)
                position(0)
            }

    // 着色器程序ID引用
    private var program: Int = 0

    init {
        val vertexCode: String =
            FileLoader.loadShader(R.raw.vertex_shader, MyApplication.get().resources)
        val vertexShader: Int = loadShader(GLES30.GL_VERTEX_SHADER, vertexCode)
        val fragmentCode: String =
            FileLoader.loadShader(R.raw.fragment_shader, MyApplication.get().resources)
        val fragmentShader: Int = loadShader(GLES30.GL_FRAGMENT_SHADER, fragmentCode)

        program = GLES30.glCreateProgram().also {
            // 把顶点着色器添加到程序对象
            GLES30.glAttachShader(it, vertexShader)
            // 把片段着色器添加到程序对象
            GLES30.glAttachShader(it, fragmentShader)
            // 连接并创建一个可执行的OpenGL ES程序对象
            GLES30.glLinkProgram(it)
        }

    }

    // 加载着色器
    private fun loadShader(type: Int, shaderCode: String): Int {
        // glCreateShader函数创建一个顶点着色器或者片段着色器,并返回新创建着色器的ID引用
        val shader = GLES30.glCreateShader(type)
        GLES30.glShaderSource(shader, shaderCode)
        GLES30.glCompileShader(shader)
        return shader
    }

    // 绘制
    fun draw() {

        // 激活着色器程序,把程序添加到OpenGL ES环境
        GLES30.glUseProgram(program)
        // 获取顶点着色器中的vPosition变量(因为之前已经编译过着色器代码,所以可以从着色器程序中获取);用唯一ID表示
        val position = GLES30.glGetAttribLocation(program, "vPosition")

        // 允许操作顶点对象position
        GLES30.glEnableVertexAttribArray(position)

        // 将顶点数据传递给position指向的vPosition变量;将顶点属性与顶点缓冲对象关联
        GLES30.glVertexAttribPointer(
            position, COORDS_PER_VERTEX, GLES30.GL_FLOAT,
            false, vertexStride, vertexBuffer)

        // 获取片段着色器中的vColor变量
        val colorHandle = GLES30.glGetUniformLocation(program, "vColor")
        // 通过colorHandle设置绘制的颜色值
        GLES30.glUniform4fv(colorHandle, 1, color, 0)
        // 按drawListBuffer中指定的顺序绘制四边形
        GLES30.glDrawElements(
            GLES30.GL_TRIANGLES, drawOrder.size,
            GLES30.GL_UNSIGNED_SHORT, drawListBuffer
        )

        // 操作完后,取消允许操作顶点对象position
        GLES30.glDisableVertexAttribArray(position)

    }


}