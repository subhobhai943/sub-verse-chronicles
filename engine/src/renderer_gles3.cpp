#include "renderer_gles3.h"
#include "logger.h"

#include <GLES3/gl3.h>
#include <cmath>
#include <vector>

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
    if (texture_id_) glDeleteTextures(1, &texture_id_);
}

void RendererGLES3::createCheckerboardTexture() {
    const int width = 64;
    const int height = 64;
    std::vector<GLubyte> pixels(width * height * 4);

    for (int y = 0; y < height; ++y) {
        for (int x = 0; x < width; ++x) {
            // Checkboard pattern
            bool isWhite = ((x / 8) + (y / 8)) % 2 == 0;
            int i = (y * width + x) * 4;
            if (isWhite) {
                pixels[i+0] = 255; pixels[i+1] = 255; pixels[i+2] = 255; pixels[i+3] = 255;
            } else {
                // SUB-verse purple
                pixels[i+0] = 100; pixels[i+1] = 0;   pixels[i+2] = 200; pixels[i+3] = 255;
            }
        }
    }

    glGenTextures(1, &texture_id_);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    LOGI("Created checkerboard texture id: %d", texture_id_);
}

void RendererGLES3::onSurfaceCreated() {
    LOGI("RendererGLES3::onSurfaceCreated()");

    // 1. Create Texture
    createCheckerboardTexture();

    // 2. Shaders
    const char* vsrc = R"(
        #version 300 es
        layout(location = 0) in vec2 aPos;
        layout(location = 1) in vec2 aTexCoord;
        out vec2 vTexCoord;
        void main() {
            vTexCoord = aTexCoord;
            gl_Position = vec4(aPos, 0.0, 1.0);
        }
    )";

    const char* fsrc = R"(
        #version 300 es
        precision mediump float;
        in vec2 vTexCoord;
        out vec4 fragColor;
        uniform sampler2D uTexture;
        void main() {
            fragColor = texture(uTexture, vTexCoord);
        }
    )";

    GLuint vs = Compile(GL_VERTEX_SHADER, vsrc);
    GLuint fs = Compile(GL_FRAGMENT_SHADER, fsrc);
    program_ = Link(vs, fs);
    glDeleteShader(vs);
    glDeleteShader(fs);

    // 3. Geometry (Full screen quad)
    // x, y, u, v
    const float verts[] = {
        -1.0f,  1.0f, 0.0f, 0.0f, // Top-left
        -1.0f, -1.0f, 0.0f, 1.0f, // Bottom-left
         1.0f,  1.0f, 1.0f, 0.0f, // Top-right
         1.0f, -1.0f, 1.0f, 1.0f  // Bottom-right
    };

    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);

    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);

    // Attribute 0: Pos (2 floats)
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // Attribute 1: TexCoord (2 floats)
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindVertexArray(0);
}

void RendererGLES3::onSurfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
}

void RendererGLES3::onDrawFrame(float tSeconds) {
    // Clear to dark gray
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    glUseProgram(program_);
    
    // Bind texture
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture_id_);
    GLint loc = glGetUniformLocation(program_, "uTexture");
    glUniform1i(loc, 0);

    // Draw Quad
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

} // namespace subverse
