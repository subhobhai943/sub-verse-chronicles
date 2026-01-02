#include "engine.h"
#include "logger.h"
#include "renderer_gles3.h"
#include "asset_manager.h"
#include "sprite_renderer.h"
#include "dialogue_system.h"
#include "story_manager.h"
#include "input_manager.h"
#include "texture.h"

namespace subverse {

static Engine* g_engine = nullptr;

Engine::Engine() {
    renderer_ = new RendererGLES3();
    assetMgr_ = new AssetManager();
    spriteRenderer_ = new SpriteRenderer();
    dialogueSys_ = new DialogueSystem();
    storyMgr_ = new StoryManager();
    inputMgr_ = new InputManager();

    bgTexture_ = new Texture();
    charTexture_ = new Texture();
    dialogueBoxTex_ = new Texture();
}

Engine::~Engine() {
    delete dialogueBoxTex_;
    delete charTexture_;
    delete bgTexture_;
    delete inputMgr_;
    delete storyMgr_;
    delete dialogueSys_;
    delete spriteRenderer_;
    delete assetMgr_;
    delete renderer_;
}

void Engine::init(AAssetManager* assetMgr) {
    std::lock_guard<std::mutex> lk(mtx_);
    assetMgr_->init(assetMgr);
}

void Engine::onSurfaceCreated() {
    std::lock_guard<std::mutex> lk(mtx_);
    renderer_->onSurfaceCreated();
    spriteRenderer_->init();

    if (!initialized_) {
        loadGameAssets();
        initialized_ = true;
    }
}

void Engine::onSurfaceChanged(int width, int height) {
    std::lock_guard<std::mutex> lk(mtx_);
    width_ = width;
    height_ = height;
    renderer_->onSurfaceChanged(width, height);
}

void Engine::onDrawFrame() {
    std::lock_guard<std::mutex> lk(mtx_);
    updateGame();
    renderGame();
}

void Engine::loadGameAssets() {
    // Placeholder art for now (engine-ready). Replace with real PNG decode later.
    bgTexture_->createSolid(512, 512, 20, 30, 60, 255);
    charTexture_->createSolid(256, 512, 200, 150, 180, 255);
    dialogueBoxTex_->createSolid(512, 128, 10, 10, 10, 220);

    std::string script = assetMgr_->loadText("story/chapter1.vns");
    if (script.empty()) {
        script = "@node start\nNarrator: Missing story/chapter1.vns\n";
    }

    storyMgr_->loadScript(script);
    storyMgr_->start();
}

void Engine::advance() {
    std::lock_guard<std::mutex> lk(mtx_);
    auto* node = storyMgr_->getCurrentNode();
    if (!node) return;

    if (node->type == "choice") {
        // If UI calls advance during a choice, default to first choice.
        storyMgr_->selectChoice(0);
    } else {
        storyMgr_->advance();
    }
}

void Engine::choose(int index) {
    std::lock_guard<std::mutex> lk(mtx_);
    storyMgr_->selectChoice(index);
}

std::string Engine::getSpeaker() {
    std::lock_guard<std::mutex> lk(mtx_);
    return dialogueSys_->getCurrentLine().speaker;
}

std::string Engine::getText() {
    std::lock_guard<std::mutex> lk(mtx_);
    return dialogueSys_->getCurrentLine().text;
}

int Engine::getChoiceCount() {
    std::lock_guard<std::mutex> lk(mtx_);
    return (int)dialogueSys_->getChoices().size();
}

std::string Engine::getChoiceText(int index) {
    std::lock_guard<std::mutex> lk(mtx_);
    const auto& ch = dialogueSys_->getChoices();
    if (index < 0 || index >= (int)ch.size()) return "";
    return ch[index].text;
}

void Engine::updateGame() {
    auto* node = storyMgr_->getCurrentNode();
    if (!node) return;

    if (node->type == "dialogue") {
        dialogueSys_->setText(node->speaker, node->text);
        dialogueSys_->clearChoices();
    } else if (node->type == "choice") {
        dialogueSys_->setText(node->speaker, node->text);
        std::vector<Choice> choices;
        for (size_t i = 0; i < node->choices.size(); ++i) {
            choices.push_back({node->choices[i], node->targets[i]});
        }
        dialogueSys_->setChoices(choices);
    } else {
        // scene nodes have no text
        dialogueSys_->setText("", "");
        dialogueSys_->clearChoices();
    }
}

void Engine::renderGame() {
    renderer_->renderBackground();

    spriteRenderer_->begin();

    // Background
    Sprite bg{0, 0, (float)width_, (float)height_, 1.0f, bgTexture_};
    spriteRenderer_->drawSprite(bg, (float)width_, (float)height_);

    // Character (simple centered)
    float charW = 300.0f;
    float charH = 600.0f;
    Sprite character{(float)width_/2.0f - charW/2.0f, (float)height_/2.0f - charH, charW, charH, 0.95f, charTexture_};
    spriteRenderer_->drawSprite(character, (float)width_, (float)height_);

    // Dialogue box (visual only; real text is drawn by Android overlay)
    if (!dialogueSys_->getCurrentLine().text.empty()) {
        float boxH = 220.0f;
        Sprite box{40.0f, (float)height_ - boxH - 40.0f, (float)width_ - 80.0f, boxH, 0.85f, dialogueBoxTex_};
        spriteRenderer_->drawSprite(box, (float)width_, (float)height_);
    }

    spriteRenderer_->end();
}

void Engine::onTouchDown(float x, float y) {
    inputMgr_->onTouchDown(x, y);
}

void Engine::onTouchUp(float x, float y) {
    inputMgr_->onTouchUp(x, y);
}

Engine& GetEngine() {
    if (!g_engine) g_engine = new Engine();
    return *g_engine;
}

} // namespace subverse
