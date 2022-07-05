package com.three.gllearning

import android.Manifest
import android.content.pm.PackageManager
import androidx.appcompat.app.AppCompatActivity
import android.os.Bundle
import android.view.View
import android.widget.TextView
import androidx.core.app.ActivityCompat
import androidx.core.content.ContextCompat
import com.three.gllearning.databinding.ActivityMainBinding

class MainActivity : AppCompatActivity() {

    private lateinit var binding: ActivityMainBinding

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)


        binding = ActivityMainBinding.inflate(layoutInflater)
        setContentView(binding.root)
        binding.preview.setOnClickListener {
            binding.preview.visibility = View.GONE
//            if (ContextCompat.checkSelfPermission(
//                    this,
//                    Manifest.permission.CAMERA
//                ) == PackageManager.PERMISSION_GRANTED
//            ) {
//                //Toast.makeText(MainActivity.this,"您申请了动态权限",Toast.LENGTH_SHORT).show();
//            } else {
//                //否则去请求相机权限
//            }
            ActivityCompat.requestPermissions(this, arrayOf(Manifest.permission.CAMERA), 1)
        }


    }

    override fun onRequestPermissionsResult(
        requestCode: Int,
        permissions: Array<out String>,
        grantResults: IntArray
    ) {
        super.onRequestPermissionsResult(requestCode, permissions, grantResults)
        if (requestCode == 1) {
            if (grantResults.isNotEmpty() && grantResults[0] == PackageManager.PERMISSION_GRANTED) {
                binding.glSurface.visibility = View.VISIBLE

            }
        }
    }

}