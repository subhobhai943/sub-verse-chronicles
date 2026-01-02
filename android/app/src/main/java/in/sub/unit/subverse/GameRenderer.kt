package `in`.sub.unit.subverse

import android.content.Context
import android.opengl.GLSurfaceView
import javax.microedition.khronos.egl.EGLConfig
import javax.microedition.khronos.opengles.GL10

class GameRenderer(
    private val context: Context,
    private val engine: NativeEngine
) : GLSurfaceView.Renderer {

    override fun onSurfaceCreated(gl: GL10?, config: EGLConfig?) {
        engine.init(context.assets)
        engine.onSurfaceCreated()
    }

    override fun onSurfaceChanged(gl: GL10?, width: Int, height: Int) {
        engine.onSurfaceChanged(width, height)
    }

    override fun onDrawFrame(gl: GL10?) {
        engine.onDrawFrame()
    }
}
