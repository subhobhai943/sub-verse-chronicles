#include "renderer_gles3.h"
#include "logger.h"
#include <GLES3/gl3.h>

namespace subverse {

RendererGLES3::RendererGLES3() = default;
RendererGLES3::~RendererGLES3() = default;

void RendererGLES3::onSurfaceCreated() {
    LOGI("RendererGLES3::onSurfaceCreated()");
    glDisable(GL_DEPTH_TEST);
}

void RendererGLES3::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void RendererGLES3::renderBackground() {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
}

} // namespace subverse
