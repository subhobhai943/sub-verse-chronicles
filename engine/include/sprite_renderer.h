#pragma once
#include "texture.h"
#include <GLES3/gl3.h>

namespace subverse {

struct Sprite {
    float x, y, w, h;
    float alpha;
    Texture* texture;
};

class SpriteRenderer {
public:
    SpriteRenderer();
    ~SpriteRenderer();
    
    void init();
    void begin();
    void drawSprite(const Sprite& sprite, float screenW, float screenH);
    void end();
    
private:
    GLuint compileShader(GLenum type, const char* src);
    GLuint createProgram(GLuint vs, GLuint fs);

    GLuint shaderProgram_ = 0;
    GLuint vao_ = 0;
    GLuint vbo_ = 0;
};

} // namespace subverse
