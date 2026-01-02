#pragma once

#include <android/asset_manager.h>
#include <string>
#include <vector>
#include <cstdint>

namespace subverse {

class AssetManager {
public:
    void init(AAssetManager* mgr);
    std::vector<uint8_t> loadFile(const std::string& path);
    std::string loadText(const std::string& path);

private:
    AAssetManager* assetMgr_ = nullptr;
};

} // namespace subverse
