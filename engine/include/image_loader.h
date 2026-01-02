#pragma once

#include <string>

namespace subverse {

class Texture;

class ImageLoader {
public:
    static bool loadPNG(const std::string& path, Texture* outTexture);
    static bool loadPNGFromMemory(const unsigned char* data, int len, Texture* outTexture);
};

} // namespace subverse
