#pragma once

namespace subverse {

class RendererGLES3 {
public:
    RendererGLES3();
    ~RendererGLES3();

    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onDrawFrame(float tSeconds);

private:
    unsigned int program_ = 0;
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
};

} // namespace subverse
