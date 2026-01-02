#include "sprite_renderer.h"
#include "texture.h"
#include "logger.h"
#include <vector>

namespace subverse {

// Simple vertex shader for sprites
static const char* kSpriteVs = R"(#version 300 es
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;

uniform mat4 uProjection;
uniform mat4 uModel;

out vec2 TexCoord;

void main() {
    gl_Position = uProjection * uModel * vec4(aPos, 0.0, 1.0);
    TexCoord = aTexCoord;
}
)";

// Fragment shader
static const char* kSpriteFs = R"(#version 300 es
precision mediump float;

in vec2 TexCoord;
out vec4 FragColor;

uniform sampler2D uTexture;
uniform float uAlpha;

void main() {
    vec4 texColor = texture(uTexture, TexCoord);
    FragColor = vec4(texColor.rgb, texColor.a * uAlpha);
}
)";

SpriteRenderer::SpriteRenderer() : shaderProgram_(0), vao_(0), vbo_(0) {}

SpriteRenderer::~SpriteRenderer() {
    if (vao_) glDeleteVertexArrays(1, &vao_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (shaderProgram_) glDeleteProgram(shaderProgram_);
}

void SpriteRenderer::init() {
    // Compile shaders
    GLuint vs = compileShader(GL_VERTEX_SHADER, kSpriteVs);
    GLuint fs = compileShader(GL_FRAGMENT_SHADER, kSpriteFs);
    shaderProgram_ = createProgram(vs, fs);

    // Quad vertices (x, y, u, v)
    float vertices[] = { 
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f, 
    
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glGenVertexArrays(1, &vao_);
    glGenBuffers(1, &vbo_);

    glBindVertexArray(vao_);

    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Pos
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);

    // TexCoord
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
}

void SpriteRenderer::begin() {
    // Enable blending for transparency
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}

void SpriteRenderer::end() {
    glDisable(GL_BLEND);
}

void SpriteRenderer::drawSprite(const Sprite& sprite, float screenW, float screenH) {
    if (!sprite.texture) return;

    glUseProgram(shaderProgram_);

    // Projection (ortho)
    // 2D projection matrix 0..screenW, screenH..0 (top-left origin usually, but let's do bottom-left 0,0 for standard GL)
    
    // Simple ortho matrix
    float left = 0.0f;
    float right = screenW;
    float bottom = 0.0f;
    float top = screenH;
    float near = -1.0f;
    float far = 1.0f;
    
    float r_l = right - left;
    float t_b = top - bottom;
    float f_n = far - near;
    
    float tx = -(right + left) / r_l;
    float ty = -(top + bottom) / t_b;
    float tz = -(far + near) / f_n;

    float projection[16] = {
        2.0f/r_l, 0.0f, 0.0f, 0.0f,
        0.0f, 2.0f/t_b, 0.0f, 0.0f,
        0.0f, 0.0f, -2.0f/f_n, 0.0f,
        tx, ty, tz, 1.0f
    };

    // Model matrix
    // T * S
    float model[16] = {
        sprite.w, 0.0f, 0.0f, 0.0f,
        0.0f, sprite.h, 0.0f, 0.0f,
        0.0f, 0.0f, 1.0f, 0.0f,
        sprite.x, sprite.y, 0.0f, 1.0f
    };

    GLint projLoc = glGetUniformLocation(shaderProgram_, "uProjection");
    GLint modelLoc = glGetUniformLocation(shaderProgram_, "uModel");
    GLint alphaLoc = glGetUniformLocation(shaderProgram_, "uAlpha");
    GLint texLoc = glGetUniformLocation(shaderProgram_, "uTexture");

    glUniformMatrix4fv(projLoc, 1, GL_FALSE, projection);
    glUniformMatrix4fv(modelLoc, 1, GL_FALSE, model);
    glUniform1f(alphaLoc, sprite.alpha);
    glUniform1i(texLoc, 0);

    glActiveTexture(GL_TEXTURE0);
    sprite.texture->bind();

    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glBindVertexArray(0);
}

GLuint SpriteRenderer::compileShader(GLenum type, const char* src) {
    GLuint shader = glCreateShader(type);
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    
    // Check error
    GLint success;
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        LOGE("Shader compile error: %s", infoLog);
    }
    return shader;
}

GLuint SpriteRenderer::createProgram(GLuint vs, GLuint fs) {
    GLuint prog = glCreateProgram();
    glAttachShader(prog, vs);
    glAttachShader(prog, fs);
    glLinkProgram(prog);
    
    GLint success;
    glGetProgramiv(prog, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[512];
        glGetProgramInfoLog(prog, 512, nullptr, infoLog);
        LOGE("Program link error: %s", infoLog);
    }
    
    glDeleteShader(vs);
    glDeleteShader(fs);
    return prog;
}

} // namespace subverse
