package com.three.gllearning

import android.opengl.GLES20
import android.opengl.GLSurfaceView
import com.three.gllearning.geometric.Triangle
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * @Description: java 层渲染器
 * @ClassName: MyGLRender
 * @Package: com.three.gllearning
 * @Date: 2022/6/28 16:38
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class MyGLRender: GLSurfaceView.Renderer {

    private lateinit var triangle: Triangle

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // 设置背景色为黑色
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
        triangle = Triangle()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        // 上面提到OpenGL使用的是标准化设备坐标;
        GLES20.glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT)
        // 绘制三角形
        triangle.draw()
    }
}