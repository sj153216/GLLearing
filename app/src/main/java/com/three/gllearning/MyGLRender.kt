package com.three.gllearning

import android.graphics.SurfaceTexture
import android.opengl.GLES30
import android.opengl.GLSurfaceView
import com.three.gllearning.camera.CameraDrawer
import com.three.gllearning.camera.CameraHelper
import com.three.gllearning.geometric.Square
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
class MyGLRender(private val frameAvailableListener: SurfaceTexture.OnFrameAvailableListener) : GLSurfaceView.Renderer {

    private lateinit var triangle: Triangle
    private lateinit var square: Square

    private lateinit var cameraDrawer: CameraDrawer
    private val cameraManager: CameraHelper = CameraHelper()

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        // 设置背景色为黑色
        GLES30.glClearColor(0.0f, 0.0f, 0.0f, 1.0f)
//        triangle = Triangle()
//        square = Square()
        cameraDrawer = CameraDrawer()
        cameraDrawer.getSurfaceTexture()?.setOnFrameAvailableListener(frameAvailableListener)
        cameraManager.openCamera()
        cameraManager.setPreviewTexture(cameraDrawer.getSurfaceTexture())
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        // 上面提到OpenGL使用的是标准化设备坐标;
        GLES30.glViewport(0, 0, width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        GLES30.glClear(GLES30.GL_COLOR_BUFFER_BIT)
        // 绘制三角形
//        triangle.draw()
        // 绘制四边形
//        square.draw()
        cameraDrawer.getSurfaceTexture()?.updateTexImage()
        cameraDrawer.draw()

    }
}