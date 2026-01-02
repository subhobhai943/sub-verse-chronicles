#pragma once

#include <cstdint>

namespace subverse {

class RendererGLES3;

class Engine {
public:
    Engine();
    ~Engine();

    void init();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onDrawFrame();

private:
    RendererGLES3* renderer_;
    int width_ = 0;
    int height_ = 0;
};

Engine& GetEngine();

} // namespace subverse
