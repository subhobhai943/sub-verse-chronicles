package `in`.sub.unit.subverse

import android.content.res.AssetManager

class NativeEngine {
    companion object {
        init {
            System.loadLibrary("subverse-engine")
        }
    }

    external fun init(assetManager: AssetManager)
    external fun getVersion(): String
    external fun onSurfaceCreated()
    external fun onSurfaceChanged(width: Int, height: Int)
    external fun onDrawFrame()
    external fun onTouchDown(x: Float, y: Float)
    external fun onTouchUp(x: Float, y: Float)
}
