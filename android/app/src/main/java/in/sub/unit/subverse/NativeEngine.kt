package `in`.sub.unit.subverse

class NativeEngine {
    companion object {
        init {
            System.loadLibrary("subverse-engine")
        }
    }

    external fun init()
    external fun getVersion(): String

    // Render lifecycle hooks (called by GLSurfaceView.Renderer)
    external fun onSurfaceCreated()
    external fun onSurfaceChanged(width: Int, height: Int)
    external fun onDrawFrame()
}
