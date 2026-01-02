#include "engine.h"
#include "logger.h"
#include "renderer_gles3.h"

namespace subverse {

static Engine* g_engine = nullptr;

Engine::Engine() {
    renderer_ = new RendererGLES3();
}

Engine::~Engine() {
    delete renderer_;
    renderer_ = nullptr;
}

void Engine::init() {
    LOGI("Engine::init()");
}

void Engine::onSurfaceCreated() {
    LOGI("Engine::onSurfaceCreated()");
    renderer_->onSurfaceCreated();
}

void Engine::onSurfaceChanged(int width, int height) {
    width_ = width;
    height_ = height;
    LOGI("Engine::onSurfaceChanged(%d, %d)", width, height);
    renderer_->onSurfaceChanged(width, height);
}

void Engine::onDrawFrame() {
    // cheap time source: frame counter -> seconds-ish
    static uint64_t frame = 0;
    frame++;
    const float t = (frame % 6000) / 60.0f;
    renderer_->onDrawFrame(t);
}

Engine& GetEngine() {
    if (!g_engine) g_engine = new Engine();
    return *g_engine;
}

} // namespace subverse
