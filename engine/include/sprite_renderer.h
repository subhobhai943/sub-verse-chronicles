#pragma once
#include "texture.h"
#include <memory>

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
    unsigned int program_ = 0;
    unsigned int vao_ = 0;
    unsigned int vbo_ = 0;
};

} // namespace subverse
