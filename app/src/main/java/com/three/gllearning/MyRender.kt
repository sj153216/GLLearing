package com.three.gllearning

import android.graphics.Bitmap
import android.graphics.BitmapFactory
import android.opengl.GLSurfaceView
import android.os.Environment
import android.util.Log
import com.three.gllearning.util.FileLoader
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
class MyRender() : GLSurfaceView.Renderer {

    private lateinit var vertexCode: String
    private lateinit var fragmentCode: String
    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        Log.d("learning-gl", "onSurfaceCreated");
        vertexCode = FileLoader.loadShader(R.raw.vertex_shader, MyApplication.get().resources)
        fragmentCode = FileLoader.loadShader(R.raw.fragment_shader, MyApplication.get().resources)

        val bitmap = BitmapFactory.decodeResource(MyApplication.get().resources, R.drawable.img)
        native_texImage2D(bitmap, Environment.getExternalStorageDirectory().absolutePath)
        nativeOnSurfaceCreated(vertexCode, fragmentCode)
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        nativeOnSurfaceChanged()

    }

    override fun onDrawFrame(gl: GL10?) {
        nativeOnDrawFrame()
    }

    companion object {
        init {
            System.loadLibrary("gllearning")
        }
    }

    private external fun nativeInit()
    private external fun nativeOnSurfaceCreated(vertexCode: String, fragmentCode: String)
    private external fun nativeOnSurfaceChanged()
    private external fun nativeOnDrawFrame()

    private external fun native_texImage2D(bitmap: Bitmap, path: String)

}