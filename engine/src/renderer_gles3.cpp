#include "renderer_gles3.h"
#include "logger.h"

#include <GLES3/gl3.h>
#include <cmath>

namespace subverse {

static GLuint Compile(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);

    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[1024];
        GLsizei len = 0;
        glGetShaderInfoLog(s, sizeof(log), &len, log);
        LOGE("Shader compile error: %s", log);
    }
    return s;
}

static GLuint Link(GLuint vs, GLuint fs) {
    GLuint p = glCreateProgram();
    glAttachShader(p, vs);
    glAttachShader(p, fs);
    glLinkProgram(p);

    GLint ok = 0;
    glGetProgramiv(p, GL_LINK_STATUS, &ok);
    if (!ok) {
        char log[1024];
        GLsizei len = 0;
        glGetProgramInfoLog(p, sizeof(log), &len, log);
        LOGE("Program link error: %s", log);
    }
    return p;
}

RendererGLES3::RendererGLES3() = default;
RendererGLES3::~RendererGLES3() {
    if (program_) glDeleteProgram(program_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
}

void RendererGLES3::onSurfaceCreated() {
    LOGI("RendererGLES3::onSurfaceCreated()");

    const char* vsrc = R"(
        #version 300 es
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec3 aColor;
        out vec3 vColor;
        void main() {
            vColor = aColor;
            gl_Position = vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fsrc = R"(
        #version 300 es
        precision mediump float;
        in vec3 vColor;
        out vec4 fragColor;
        void main() {
            fragColor = vec4(vColor, 1.0);
        }
    )";

    GLuint vs = Compile(GL_VERTEX_SHADER, vsrc);
    GLuint fs = Compile(GL_FRAGMENT_SHADER, fsrc);
    program_ = Link(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    // Full-screen triangle (fewer vertices than a quad)
    // pos(x,y), color(r,g,b)
    const float verts[] = {
        -1.0f, -1.0f,  0.10f, 0.10f, 0.35f,
         3.0f, -1.0f,  0.15f, 0.10f, 0.55f,
        -1.0f,  3.0f,  0.20f, 0.15f, 0.75f,
    };

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);

    glDisable(GL_DEPTH_TEST);
}

void RendererGLES3::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void RendererGLES3::onDrawFrame(float tSeconds) {
    // subtle animated clear color to prove the render loop works
    const float r = 0.08f + 0.04f * std::sin(tSeconds * 0.7f);
    const float g = 0.06f + 0.04f * std::sin(tSeconds * 0.9f);
    const float b = 0.12f + 0.06f * std::sin(tSeconds * 0.5f);

    glClearColor(r, g, b, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_);
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

} // namespace subverse
