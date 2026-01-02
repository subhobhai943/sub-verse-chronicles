#pragma once

namespace subverse {

class RendererGLES3 {
public:
    RendererGLES3();
    ~RendererGLES3();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void renderBackground();
};

} // namespace subverse
