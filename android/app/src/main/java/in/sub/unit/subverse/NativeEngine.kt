package `in`.sub.unit.subverse

class NativeEngine {
    companion object {
        init {
            System.loadLibrary("subverse-engine")
        }
    }

    /**
     * Initializes the C++ engine core.
     */
    external fun init()

    /**
     * Returns the engine version string from C++.
     */
    external fun getVersion(): String
}