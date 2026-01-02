#include "sprite_renderer.h"
#include "logger.h"
#include <GLES3/gl3.h>

namespace subverse {

static const char* SPRITE_VS = R"(
#version 300 es
layout(location = 0) in vec2 aPos;
layout(location = 1) in vec2 aTexCoord;
out vec2 vTexCoord;
uniform mat4 uTransform;
void main() {
    vTexCoord = aTexCoord;
    gl_Position = uTransform * vec4(aPos, 0.0, 1.0);
}
)";

static const char* SPRITE_FS = R"(
#version 300 es
precision mediump float;
in vec2 vTexCoord;
out vec4 fragColor;
uniform sampler2D uTexture;
uniform float uAlpha;
void main() {
    vec4 texColor = texture(uTexture, vTexCoord);
    fragColor = vec4(texColor.rgb, texColor.a * uAlpha);
}
)";

static GLuint CompileShader(GLenum type, const char* src) {
    GLuint s = glCreateShader(type);
    glShaderSource(s, 1, &src, nullptr);
    glCompileShader(s);
    GLint ok = 0;
    glGetShaderiv(s, GL_COMPILE_STATUS, &ok);
    if (!ok) {
        char log[512];
        glGetShaderInfoLog(s, 512, nullptr, log);
        LOGE("Shader error: %s", log);
    }
    return s;
}

SpriteRenderer::SpriteRenderer() = default;
SpriteRenderer::~SpriteRenderer() {
    if (program_) glDeleteProgram(program_);
    if (vbo_) glDeleteBuffers(1, &vbo_);
    if (vao_) glDeleteVertexArrays(1, &vao_);
}

void SpriteRenderer::init() {
    GLuint vs = CompileShader(GL_VERTEX_SHADER, SPRITE_VS);
    GLuint fs = CompileShader(GL_FRAGMENT_SHADER, SPRITE_FS);
    program_ = glCreateProgram();
    glAttachShader(program_, vs);
    glAttachShader(program_, fs);
    glLinkProgram(program_);
    glDeleteShader(vs);
    glDeleteShader(fs);
    
    float verts[] = {
        0.0f, 1.0f, 0.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 0.0f,
        1.0f, 0.0f, 1.0f, 1.0f
    };
    
    glGenVertexArrays(1, &vao_);
    glBindVertexArray(vao_);
    glGenBuffers(1, &vbo_);
    glBindBuffer(GL_ARRAY_BUFFER, vbo_);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), verts, GL_STATIC_DRAW);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), 0);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4*sizeof(float), (void*)(2*sizeof(float)));
    glBindVertexArray(0);
    
    LOGI("SpriteRenderer initialized");
}

void SpriteRenderer::begin() {
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glUseProgram(program_);
}

void SpriteRenderer::drawSprite(const Sprite& sprite, float screenW, float screenH) {
    if (!sprite.texture) return;
    
    // Build transform matrix (simple ortho projection)
    float l = sprite.x;
    float r = sprite.x + sprite.w;
    float b = sprite.y + sprite.h;
    float t = sprite.y;
    
    float mat[16] = {
        2.0f * sprite.w / screenW, 0, 0, 0,
        0, 2.0f * sprite.h / screenH, 0, 0,
        0, 0, 1, 0,
        2.0f * (sprite.x + sprite.w/2.0f) / screenW - 1.0f,
        -(2.0f * (sprite.y + sprite.h/2.0f) / screenH - 1.0f),
        0, 1
    };
    
    GLint transformLoc = glGetUniformLocation(program_, "uTransform");
    glUniformMatrix4fv(transformLoc, 1, GL_FALSE, mat);
    
    GLint alphaLoc = glGetUniformLocation(program_, "uAlpha");
    glUniform1f(alphaLoc, sprite.alpha);
    
    sprite.texture->bind(0);
    GLint texLoc = glGetUniformLocation(program_, "uTexture");
    glUniform1i(texLoc, 0);
    
    glBindVertexArray(vao_);
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glBindVertexArray(0);
}

void SpriteRenderer::end() {
    glDisable(GL_BLEND);
}

} // namespace subverse
