package com.three.gllearning

import android.content.Context
import android.graphics.BitmapFactory
import android.graphics.SurfaceTexture
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
class MyGLSurfaceView(context: Context?, attrs: AttributeSet?) : GLSurfaceView(context, attrs),
    SurfaceTexture.OnFrameAvailableListener {

    private var glRender: MyGLRender

    init {
        this.setEGLContextClientVersion(2)
        glRender = MyGLRender(this)
        setRenderer(glRender)
        renderMode = RENDERMODE_WHEN_DIRTY
        val bitmap = BitmapFactory.decodeResource(context?.resources, R.drawable.avatar)
        glRender.setImageBitmap(bitmap)
    }

    override fun onFrameAvailable(surfaceTexture: SurfaceTexture?) {

        // 请求绘制，会触发 render 的 onDrawFrame
        requestRender()

    }


}