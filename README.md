# 🎮 SUB-verse Chronicles

**A production-ready visual novel game engine built with C++ and OpenGL ES 3.0 for Android.**

[![Download Assets](https://github.com/subhobhai943/sub-verse-chronicles/actions/workflows/download-assets.yml/badge.svg)](https://github.com/subhobhai943/sub-verse-chronicles/actions/workflows/download-assets.yml)

## ✨ Features

- **Custom C++ Game Engine**: OpenGL ES 3.0 renderer with sprite batching
- **Visual Novel System**: Branching dialogue, choices, and story scripting (`.vns` format)
- **Android Dialogue Overlay**: Native TextViews + buttons for text display
- **PNG Asset Loading**: `stb_image.h` integration for real artwork
- **Production UI**: Adaptive app icon, fullscreen immersive mode, touch controls
- **Automated Asset Pipeline**: GitHub Actions downloads CC0 art from OpenGameArt.org

## 🎨 Art Assets

All visual assets are **free and open source** (CC0/Public Domain):
- 5 background scenes (bedroom, forest, castle, sky, battle)
- 4 character sprites (protagonist, girl, wizard, monster)
- Assets auto-downloaded via GitHub Actions workflow
- Full credits in `android/app/src/main/assets/CREDITS.txt`

## 🚀 Quick Start

### Download Assets

1. Go to [**Actions** tab](https://github.com/subhobhai943/sub-verse-chronicles/actions)
2. Click **Download Visual Novel Assets** workflow
3. Click **Run workflow** → **Run workflow**
4. Wait 1-2 minutes for assets to be downloaded and committed

### Build APK

After assets are downloaded:

1. Wait for **Android CI** build to complete automatically
2. Download `sub-verse-debug` artifact from the build
3. Extract and install `app-debug.apk` on your Android device

### Manual Build

```bash
# Clone repository
git clone https://github.com/subhobhai943/sub-verse-chronicles.git
cd sub-verse-chronicles

# Run asset download workflow (or download manually)
gh workflow run download-assets.yml

# Build with Gradle
cd android
./gradlew assembleDebug

# Install APK
adb install app/build/outputs/apk/debug/app-debug.apk
```

## 📖 Story Scripting

Edit `android/app/src/main/assets/story/chapter1.vns`:

```
@node start
@scene bedroom
@bg bedroom
@char protagonist
Narrator: You wake up in your bedroom...
@next choice1

@node choice1
@choice
Protagonist: What should I do?
> Explore the house -> explore
> Go back to sleep -> sleep

@node explore
Narrator: You venture into the unknown...
@next end

@node sleep
Narrator: You drift back to sleep. Game Over.

@node end
Narrator: To be continued...
```

## 🏗️ Engine Architecture

```
engine/
├── include/          # C++ headers
│   ├── engine.h      # Main engine singleton
│   ├── renderer_gles3.h
│   ├── sprite_renderer.h
│   ├── dialogue_system.h
│   ├── story_manager.h
│   ├── image_loader.h
│   └── stb/          # stb_image.h
├── src/              # C++ implementation
└── CMakeLists.txt

android/
├── app/src/main/
│   ├── java/.../     # Kotlin UI layer
│   │   ├── MainActivity.kt
│   │   ├── DialogueOverlay.kt
│   │   └── NativeEngine.kt
│   └── assets/       # Game data
│       ├── story/chapter1.vns
│       └── images/
│           ├── backgrounds/
│           └── characters/
└── build.gradle
```

## 🎯 Roadmap

- [x] Core OpenGL ES 3.0 engine
- [x] Visual novel dialogue system
- [x] Android UI overlay
- [x] PNG image loading (stb_image)
- [x] GitHub Actions asset pipeline
- [ ] Sound effects and music
- [ ] Save/load system
- [ ] Character animations
- [ ] Particle effects
- [ ] Localization support

## 📜 License

**Code**: MIT License (see LICENSE file)

**Assets**: CC0 / Public Domain (see `android/app/src/main/assets/CREDITS.txt`)

## 🙏 Credits

- **Engine**: Built by [subhobhai943](https://github.com/subhobhai943)
- **Art**: OpenGameArt.org community (CC0 artists)
- **Libraries**: 
  - [stb_image.h](https://github.com/nothings/stb) by Sean Barrett
  - Android NDK & OpenGL ES 3.0

---

**Made with ❤️ for the visual novel community**
