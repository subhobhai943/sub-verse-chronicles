#include "asset_manager.h"
#include "logger.h"

namespace subverse {

void AssetManager::init(AAssetManager* mgr) {
    assetMgr_ = mgr;
    LOGI("AssetManager initialized");
}

std::vector<uint8_t> AssetManager::loadFile(const std::string& path) {
    std::vector<uint8_t> data;
    if (!assetMgr_) {
        LOGE("AssetManager not initialized");
        return data;
    }
    
    AAsset* asset = AAssetManager_open(assetMgr_, path.c_str(), AASSET_MODE_BUFFER);
    if (!asset) {
        LOGE("Failed to open asset: %s", path.c_str());
        return data;
    }
    
    size_t size = AAsset_getLength(asset);
    data.resize(size);
    AAsset_read(asset, data.data(), size);
    AAsset_close(asset);
    
    LOGI("Loaded asset: %s (%zu bytes)", path.c_str(), size);
    return data;
}

std::string AssetManager::loadText(const std::string& path) {
    auto data = loadFile(path);
    return std::string(data.begin(), data.end());
}

} // namespace subverse
