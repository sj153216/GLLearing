package com.three.gllearning

import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

/**
 * @Description: 渲染器
 * @ClassName: MyRender
 * @Package: com.three.gllearning
 * @Date: 2022/6/28 14:17
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class MyRender : GLSurfaceView.Renderer {
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        nativeOnSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeOnSurfaceChanged()

    }

    override fun onDrawFrame(gl: GL10?) {
        nativeOnDrawFrame()
    }

    companion object {
        init {
            System.loadLibrary("native-lib")
        }
    }

    external fun nativeInit()
    external fun nativeOnSurfaceCreated()
    external fun nativeOnSurfaceChanged()
    external fun nativeOnDrawFrame()

}