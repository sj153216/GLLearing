package com.three.gllearning.camera

import android.hardware.Camera
import android.view.SurfaceHolder
import java.lang.Exception
import android.graphics.SurfaceTexture


/**
 * @Description: 操作相机类
 * @ClassName: CaneraHelper
 * @Package: com.three.gllearning.camera
 * @Date: 2022/6/29 19:21
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
@Suppress("DEPRECATION")
class CameraHelper {
    private lateinit var camera: Camera

    // 打开相机
    fun openCamera() {
        // 打开相机
        camera = Camera.open()
        val parameters: Camera.Parameters = camera.parameters
        // 自动对焦
        parameters.focusMode = Camera.Parameters.FOCUS_MODE_CONTINUOUS_PICTURE
        camera.parameters = parameters
        // 开始相机预览
        camera.startPreview()
    }


    // 停止相机
    fun stopCamera() {
        if (camera != null) {
            camera.stopPreview()
            camera.release()
        }
    }


    // 用SurfaceHolder承接相机预览数据
    fun setPreviewDisplay(surfaceHolder: SurfaceHolder?) {
        try {
            // 把相机预览数据传给SurfaceHolder
            camera.setPreviewDisplay(surfaceHolder)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

    // 用SurfaceTexture承接相机预览数据
    fun setPreviewTexture(surfaceTexture: SurfaceTexture?) {
        try {
            // 把相机预览数据传给SurfaceTexture
            camera.setPreviewTexture(surfaceTexture)
        } catch (e: Exception) {
            e.printStackTrace()
        }
    }

}