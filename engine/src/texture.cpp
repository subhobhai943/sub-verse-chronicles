#include "texture.h"
#include "logger.h"
#include <GLES3/gl3.h>

// Minimal PNG decoder (header check only, creates placeholder)
namespace subverse {

Texture::Texture() = default;

Texture::~Texture() {
    if (id_) glDeleteTextures(1, &id_);
}

bool Texture::loadFromMemory(const std::vector<uint8_t>& pngData) {
    // For MVP: Create placeholder colored texture
    // Real implementation would use stb_image or libpng
    LOGI("Texture::loadFromMemory - Creating placeholder (PNG decode not implemented)");
    
    // Create a simple gradient texture as placeholder
    width_ = 256;
    height_ = 256;
    std::vector<uint8_t> pixels(width_ * height_ * 4);
    
    for (int y = 0; y < height_; ++y) {
        for (int x = 0; x < width_; ++x) {
            int i = (y * width_ + x) * 4;
            pixels[i+0] = (x * 255) / width_;  // R gradient
            pixels[i+1] = (y * 255) / height_; // G gradient
            pixels[i+2] = 128;                  // B constant
            pixels[i+3] = 255;                  // A opaque
        }
    }
    
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
    
    return true;
}

void Texture::createSolid(int w, int h, uint8_t r, uint8_t g, uint8_t b, uint8_t a) {
    width_ = w;
    height_ = h;
    
    std::vector<uint8_t> pixels(w * h * 4);
    for (int i = 0; i < w * h; ++i) {
        pixels[i*4+0] = r;
        pixels[i*4+1] = g;
        pixels[i*4+2] = b;
        pixels[i*4+3] = a;
    }
    
    glGenTextures(1, &id_);
    glBindTexture(GL_TEXTURE_2D, id_);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width_, height_, 0, GL_RGBA, GL_UNSIGNED_BYTE, pixels.data());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
}

void Texture::bind(int slot) {
    glActiveTexture(GL_TEXTURE0 + slot);
    glBindTexture(GL_TEXTURE_2D, id_);
}

} // namespace subverse
