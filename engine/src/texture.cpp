#include "texture.h"
#include "logger.h"
#include <vector>

namespace subverse {

Texture::Texture() : textureID_(0), width_(0), height_(0) {}

Texture::~Texture() {
    release();
}

void Texture::createSolid(int width, int height, int r, int g, int b, int a) {
    width_ = width;
    height_ = height;

    std::vector<unsigned char> data(width * height * 4);
    for (int i = 0; i < width * height; ++i) {
        data[i * 4 + 0] = r;
        data[i * 4 + 1] = g;
        data[i * 4 + 2] = b;
        data[i * 4 + 3] = a;
    }

    createFromData(width, height, data.data());
}

void Texture::createFromData(int width, int height, const unsigned char* rgba) {
    width_ = width;
    height_ = height;

    glGenTextures(1, &textureID_);
    glBindTexture(GL_TEXTURE_2D, textureID_);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, rgba);

    glBindTexture(GL_TEXTURE_2D, 0);

    LOGI("Created texture %d (%dx%d)", textureID_, width, height);
}

void Texture::bind() {
    glBindTexture(GL_TEXTURE_2D, textureID_);
}

void Texture::release() {
    if (textureID_) {
        glDeleteTextures(1, &textureID_);
        textureID_ = 0;
    }
}

} // namespace subverse
