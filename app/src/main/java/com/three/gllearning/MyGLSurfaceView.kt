package com.three.gllearning

import android.content.Context
import android.opengl.GLSurfaceView
import android.util.AttributeSet

/**
 * @Description: surfaceView
 * @ClassName: MyGLSurfaceView
 * @Package: com.three.gllearning
 * @Date: 2022/6/28 14:16
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class MyGLSurfaceView(context: Context?, attrs: AttributeSet?) : GLSurfaceView(context, attrs) {

    private var glRender: MyGLRender

    init {
        this.setEGLContextClientVersion(2)
        glRender = MyGLRender()
        setRenderer(glRender)
        renderMode = RENDERMODE_CONTINUOUSLY

    }


}