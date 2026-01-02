#include "image_loader.h"
#include "texture.h"
#include "logger.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb/stb_image.h"

namespace subverse {

bool ImageLoader::loadPNG(const std::string& path, Texture* outTexture) {
    if (!outTexture) return false;

    int width, height, channels;
    unsigned char* data = stbi_load(path.c_str(), &width, &height, &channels, STBI_rgb_alpha);

    if (!data) {
        LOGE("Failed to load image: %s", path.c_str());
        return false;
    }

    // Create texture from loaded pixel data
    outTexture->createFromData(width, height, data);

    stbi_image_free(data);
    LOGI("Loaded PNG: %s (%dx%d, %d channels)", path.c_str(), width, height, channels);
    return true;
}

bool ImageLoader::loadPNGFromMemory(const unsigned char* data, int len, Texture* outTexture) {
    if (!outTexture || !data) return false;

    int width, height, channels;
    unsigned char* pixels = stbi_load_from_memory(data, len, &width, &height, &channels, STBI_rgb_alpha);

    if (!pixels) {
        LOGE("Failed to decode image from memory");
        return false;
    }

    outTexture->createFromData(width, height, pixels);
    stbi_image_free(pixels);
    LOGI("Loaded PNG from memory (%dx%d, %d channels)", width, height, channels);
    return true;
}

} // namespace subverse
