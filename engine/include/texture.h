#pragma once
#include <cstdint>
#include <vector>

namespace subverse {

class Texture {
public:
    Texture();
    ~Texture();
    
    bool loadFromMemory(const std::vector<uint8_t>& pngData);
    void createSolid(int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a);
    void bind(int slot = 0);
    
    int width() const { return width_; }
    int height() const { return height_; }
    
private:
    unsigned int id_ = 0;
    int width_ = 0;
    int height_ = 0;
};

} // namespace subverse
