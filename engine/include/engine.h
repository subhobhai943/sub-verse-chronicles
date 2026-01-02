#pragma once

#include <android/asset_manager.h>
#include <mutex>
#include <string>

namespace subverse {

class RendererGLES3;
class AssetManager;
class SpriteRenderer;
class DialogueSystem;
class StoryManager;
class InputManager;
class Texture;

class Engine {
public:
    Engine();
    ~Engine();

    void init(AAssetManager* assetMgr);
    void onSurfaceCreated();
    void onSurfaceChanged(int width, int height);
    void onDrawFrame();

    // VN controls
    void advance();
    void choose(int index);

    // UI readback
    std::string getSpeaker();
    std::string getText();
    int getChoiceCount();
    std::string getChoiceText(int index);

    // Legacy touch hooks
    void onTouchDown(float x, float y);
    void onTouchUp(float x, float y);

private:
    void loadGameAssets();
    void updateGame();
    void renderGame();

    std::mutex mtx_;

    RendererGLES3* renderer_;
    AssetManager* assetMgr_;
    SpriteRenderer* spriteRenderer_;
    DialogueSystem* dialogueSys_;
    StoryManager* storyMgr_;
    InputManager* inputMgr_;

    Texture* bgTexture_;
    Texture* charTexture_;
    Texture* dialogueBoxTex_;

    int width_ = 0;
    int height_ = 0;
    bool initialized_ = false;
};

Engine& GetEngine();

} // namespace subverse
