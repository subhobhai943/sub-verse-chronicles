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
    LOGI("Engine::init()");
    assetMgr_->init(assetMgr);
}

void Engine::onSurfaceCreated() {
    LOGI("Engine::onSurfaceCreated()");
    renderer_->onSurfaceCreated();
    spriteRenderer_->init();
    
    if (!initialized_) {
        loadGameAssets();
        initialized_ = true;
    }
}

void Engine::onSurfaceChanged(int width, int height) {
    width_ = width;
    height_ = height;
    LOGI("Engine::onSurfaceChanged(%d, %d)", width, height);
    renderer_->onSurfaceChanged(width, height);
}

void Engine::onDrawFrame() {
    updateGame();
    renderGame();
}

void Engine::loadGameAssets() {
    LOGI("Loading game assets...");
    
    // Create placeholder textures
    bgTexture_->createSolid(512, 512, 20, 30, 60, 255); // Dark blue background
    charTexture_->createSolid(256, 512, 200, 150, 180, 255); // Purple character
    dialogueBoxTex_->createSolid(512, 128, 10, 10, 10, 220); // Dark dialogue box
    
    // Load story script
    std::string script = assetMgr_->loadText("story/chapter1.vns");
    if (script.empty()) {
        LOGI("Story script not found, using embedded demo");
        script = R"(
@node start
@scene
@bg backgrounds/home.png
@char protagonist_neutral
Protagonist: I never expected my life to change so suddenly...
@next awakening

@node awakening
@char protagonist_surprised
Protagonist: Wait... where am I? This isn't my room!
@next realize

@node realize
Mysterious Voice: Welcome, traveler from another world.
@next choice1

@node choice1
@choice
Protagonist: What do I do?
> Ask about this world -> ask_world
> Check my status -> check_status

@node ask_world
Mysterious Voice: You are in Aethermoor, a realm of magic and adventure.
@next after_choice

@node check_status
Protagonist: I can see... a status screen? Level 1, no skills...
@next after_choice

@node after_choice
Protagonist: This is just like an RPG! My isekai adventure begins!
@next end

@node end
@scene
Narrator: To be continued...
)";
    }
    
    storyMgr_->loadScript(script);
    storyMgr_->start();
    
    LOGI("Game assets loaded");
}

void Engine::updateGame() {
    if (inputMgr_->wasTapped()) {
        auto* node = storyMgr_->getCurrentNode();
        if (node) {
            if (node->type == "choice" && !node->choices.empty()) {
                // Simple choice selection (tap anywhere = first choice)
                storyMgr_->selectChoice(0);
            } else {
                storyMgr_->advance();
            }
        }
        inputMgr_->clearTap();
    }
    
    // Update dialogue from current story node
    auto* node = storyMgr_->getCurrentNode();
    if (node) {
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
        }
    }
}

void Engine::renderGame() {
    renderer_->renderBackground();
    
    spriteRenderer_->begin();
    
    // Draw background
    Sprite bg;
    bg.x = 0;
    bg.y = 0;
    bg.w = width_;
    bg.h = height_;
    bg.alpha = 1.0f;
    bg.texture = bgTexture_;
    spriteRenderer_->drawSprite(bg, width_, height_);
    
    // Draw character
    float charW = 300;
    float charH = 600;
    Sprite character;
    character.x = width_ / 2 - charW / 2;
    character.y = height_ / 2 - charH;
    character.w = charW;
    character.h = charH;
    character.alpha = 0.9f;
    character.texture = charTexture_;
    spriteRenderer_->drawSprite(character, width_, height_);
    
    // Draw dialogue box
    if (dialogueSys_->hasText()) {
        float boxH = 200;
        Sprite dialogueBox;
        dialogueBox.x = 50;
        dialogueBox.y = height_ - boxH - 50;
        dialogueBox.w = width_ - 100;
        dialogueBox.h = boxH;
        dialogueBox.alpha = 0.85f;
        dialogueBox.texture = dialogueBoxTex_;
        spriteRenderer_->drawSprite(dialogueBox, width_, height_);
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
