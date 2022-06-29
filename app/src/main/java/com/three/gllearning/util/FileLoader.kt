package com.three.gllearning.util

import android.content.res.Resources
import java.io.BufferedReader
import java.io.InputStream
import java.io.InputStreamReader
import java.lang.Exception
import java.lang.StringBuilder

/**
 * @Description: 加载文件工具类
 * @ClassName: FileLoader
 * @Package: com.three.gllearning.util
 * @Date: 2022/6/29 09:08
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
object FileLoader {
    fun loadShader(rawId: Int, resource: Resources): String {
        val stringBuilder = StringBuilder()
        var inputStream: InputStream? = null
        var bufferReader: BufferedReader? = null
        try {
            inputStream = resource.openRawResource(rawId)
            val allLines = inputStream.bufferedReader().use(BufferedReader::readText)
            stringBuilder.append(allLines)

        } catch (e: Exception) {
            e.printStackTrace()

        } finally {
            inputStream?.close()
            bufferReader?.close()

        }
        return stringBuilder.toString()
    }
}