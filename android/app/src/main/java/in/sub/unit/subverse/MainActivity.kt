package `in`.sub.unit.subverse

import android.os.Bundle
import android.os.Handler
import android.os.Looper
import android.view.Gravity
import android.view.View
import android.widget.FrameLayout
import androidx.appcompat.app.AppCompatActivity

class MainActivity : AppCompatActivity() {

    private lateinit var surfaceView: GameSurfaceView
    private lateinit var overlay: DialogueOverlay

    private val uiHandler = Handler(Looper.getMainLooper())
    private val uiTick = object : Runnable {
        override fun run() {
            // Pull dialogue state from native and paint overlay
            val engine = surfaceView.engine
            val speaker = engine.getSpeaker()
            val text = engine.getText()
            val count = engine.getChoiceCount()
            val choices = if (count > 0) (0 until count).map { engine.getChoiceText(it) } else emptyList()

            overlay.visibility = if (text.isNotBlank()) View.VISIBLE else View.GONE
            overlay.render(speaker, text, choices)

            uiHandler.postDelayed(this, 100)
        }
    }

    override fun onCreate(savedInstanceState: Bundle?) {
        super.onCreate(savedInstanceState)

        // Fullscreen immersive
        window.decorView.systemUiVisibility = (
            View.SYSTEM_UI_FLAG_IMMERSIVE_STICKY
                or View.SYSTEM_UI_FLAG_FULLSCREEN
                or View.SYSTEM_UI_FLAG_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_LAYOUT_FULLSCREEN
                or View.SYSTEM_UI_FLAG_LAYOUT_HIDE_NAVIGATION
                or View.SYSTEM_UI_FLAG_LAYOUT_STABLE
            )

        surfaceView = GameSurfaceView(this)

        overlay = DialogueOverlay(this)
        overlay.onAdvance = { surfaceView.engine.advance() }
        overlay.onChoose = { idx -> surfaceView.engine.choose(idx) }

        val root = FrameLayout(this)
        root.addView(surfaceView, FrameLayout.LayoutParams(
            FrameLayout.LayoutParams.MATCH_PARENT,
            FrameLayout.LayoutParams.MATCH_PARENT
        ))

        val overlayParams = FrameLayout.LayoutParams(
            FrameLayout.LayoutParams.MATCH_PARENT,
            FrameLayout.LayoutParams.WRAP_CONTENT
        )
        overlayParams.gravity = Gravity.BOTTOM
        overlayParams.setMargins(32, 32, 32, 32)
        root.addView(overlay, overlayParams)

        setContentView(root)
    }

    override fun onResume() {
        super.onResume()
        surfaceView.onResume()
        uiHandler.post(uiTick)
    }

    override fun onPause() {
        super.onPause()
        uiHandler.removeCallbacks(uiTick)
        surfaceView.onPause()
    }
}
