package `in`.sub.unit.subverse

import android.content.Context
import android.opengl.GLSurfaceView

class GameSurfaceView(context: Context) : GLSurfaceView(context) {
    private val engine = NativeEngine()

    init {
        // OpenGL ES 3.0
        setEGLContextClientVersion(3)
        setRenderer(GameRenderer(engine))
        renderMode = RENDERMODE_CONTINUOUSLY
    }
}
