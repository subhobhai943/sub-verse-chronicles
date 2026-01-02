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

    // Visual novel controls
    external fun advance()
    external fun choose(index: Int)

    // Data for UI overlay
    external fun getSpeaker(): String
    external fun getText(): String
    external fun getChoiceCount(): Int
    external fun getChoiceText(index: Int): String

    // Optional touch hooks (kept for future in-engine UI)
    external fun onTouchDown(x: Float, y: Float)
    external fun onTouchUp(x: Float, y: Float)
}
