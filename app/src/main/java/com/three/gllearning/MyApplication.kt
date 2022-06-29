package com.three.gllearning

import android.app.Application

/**
 * @Description:
 * @ClassName: MyApplication
 * @Package: com.three.gllearning
 * @Date: 2022/6/29 11:24
 * <ModifyLog>
 * @ModifyContent:
 * @Author:
 * @Date: </ModifyLog>
 */
class MyApplication : Application() {


    companion object {
        lateinit var instance: MyApplication

        fun get(): MyApplication {
            return instance
        }
    }

    override fun onCreate() {
        super.onCreate()
        instance = this

    }
}