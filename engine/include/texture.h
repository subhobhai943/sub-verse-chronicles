#pragma once

#include <GLES3/gl3.h>

namespace subverse {

class Texture {
public:
    Texture();
    ~Texture();

    void createSolid(int width, int height, int r, int g, int b, int a);
    void createFromData(int width, int height, const unsigned char* rgba);
    void bind();
    void release();

    int getWidth() const { return width_; }
    int getHeight() const { return height_; }
    GLuint getID() const { return textureID_; }

private:
    GLuint textureID_;
    int width_;
    int height_;
};

} // namespace subverse
