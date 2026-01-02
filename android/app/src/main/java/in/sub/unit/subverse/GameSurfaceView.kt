package `in`.sub.unit.subverse

import android.content.Context
import android.opengl.GLSurfaceView
import android.view.MotionEvent

class GameSurfaceView(context: Context) : GLSurfaceView(context) {
    private val engine = NativeEngine()

    init {
        setEGLContextClientVersion(3)
        setRenderer(GameRenderer(context, engine))
        renderMode = RENDERMODE_CONTINUOUSLY
    }

    override fun onTouchEvent(event: MotionEvent): Boolean {
        when (event.action) {
            MotionEvent.ACTION_DOWN -> {
                engine.onTouchDown(event.x, event.y)
            }
            MotionEvent.ACTION_UP -> {
                engine.onTouchUp(event.x, event.y)
            }
        }
        return true
    }
}
