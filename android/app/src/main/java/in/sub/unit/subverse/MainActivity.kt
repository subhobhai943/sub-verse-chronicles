package `in`.sub.unit.subverse

import android.os.Bundle
import android.widget.TextView
import android.view.Gravity
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {
    private val engine = NativeEngine()

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)
        
        // Temporary UI to verify Engine connection
        val tv = TextView(this)
        tv.text = "Initializing...\n" + engine.getVersion()
        tv.textSize = 24f
        tv.gravity = Gravity.CENTER
        setContentView(tv)

        // Initialize the native engine
        // In the future, this will start the OpenGL render loop
        engine.init()
    }
}