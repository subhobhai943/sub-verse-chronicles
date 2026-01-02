# SUB-verse Chronicles - Engine Architecture

## Overview
The SUB-verse Chronicles engine is designed as a modular C++ core with an Android wrapper, optimized for visual novel gameplay with isekai RPG mechanics.

## Core Engine Modules

### 1. Renderer Module
**Responsibility**: Graphics rendering using OpenGL ES 3.0

**Components**:
- `RenderContext`: Manages OpenGL context and surface
- `SpriteRenderer`: Renders 2D sprites (characters, UI elements)
- `BackgroundRenderer`: Handles background images with transitions
- `TextRenderer`: Renders dialogue text with formatting
- `ShaderManager`: Loads and manages GLSL shaders

**Key Features**:
- Sprite batching for performance
- Texture atlas support
- Screen resolution scaling
- Transition effects (fade, slide, dissolve)

### 2. Asset Manager
**Responsibility**: Loading and caching game assets

**Components**:
- `AssetLoader`: Async asset loading from APK
- `TextureCache`: Manages texture memory
- `AudioCache`: Handles audio file buffering
- `ScriptParser`: Parses story script files

**Supported Formats**:
- Images: PNG, JPG
- Audio: OGG, MP3
- Scripts: Custom .vns format (Visual Novel Script)

### 3. Narrative Engine
**Responsibility**: Story flow and dialogue management

**Components**:
- `StoryManager`: Tracks narrative state and branches
- `DialogueSystem`: Displays text with character names
- `ChoiceManager`: Handles player decisions
- `FlagSystem`: Tracks story flags and variables

**Script Format**:
```
# Example .vns script
@scene home_morning
@bg backgrounds/home_interior.png
@char protagonist neutral

Protagonist: "Another normal day..."

@choice
> Check phone -> phone_scene
> Go outside -> outside_scene
```

### 4. Game State Manager
**Responsibility**: Manages game state and persistence

**Components**:
- `SaveManager`: Serializes/deserializes game state
- `StateStack`: Manages game states (menu, dialogue, battle)
- `ProgressTracker`: Tracks achievements and stats

**Save Format**: JSON for human-readability during development

### 5. Input Manager
**Responsibility**: Touch input processing

**Components**:
- `TouchHandler`: Processes touch events from Android
- `GestureDetector`: Recognizes swipes, taps, long-press
- `UIInteraction`: Maps touches to UI elements

### 6. Audio Engine
**Responsibility**: Music and sound effects

**Components**:
- `AudioPlayer`: OpenSL ES audio playback
- `MusicManager`: Background music with crossfade
- `SFXManager`: Sound effect trigger system

### 7. Isekai Systems (RPG Layer)
**Responsibility**: Game mechanics specific to isekai genre

**Components**:
- `CharacterStats`: HP, MP, Level, Skills
- `InventorySystem`: Item management
- `QuestManager`: Quest tracking and completion
- `SkillTree`: Ability unlocking and progression

## Android Integration Layer

### JNI Bridge
Kotlin/Java wrapper communicates with C++ engine via JNI:

```cpp
// Native interface
JNIEXP void JNICALL
Java_in_sub_unit_subverse_NativeEngine_init(JNIEnv* env, jobject obj);

JNIEXP void JNICALL
Java_in_sub_unit_subverse_NativeEngine_render(JNIEnv* env, jobject obj);
```

### Activity Structure
- `MainActivity`: Hosts GLSurfaceView
- `GameRenderer`: Implements GLSurfaceView.Renderer
- `NativeEngine`: JNI interface to C++ core

## Memory Management

### Texture Streaming
- Load high-res textures on demand
- Keep UI and current scene sprites in memory
- Unload background textures not in use

### Object Pooling
- Reuse sprite objects
- Pool dialogue boxes and UI elements
- Minimize allocations during gameplay

## Threading Model

- **Main Thread**: Android UI and lifecycle
- **Render Thread**: OpenGL rendering (GLThread)
- **Asset Thread**: Background asset loading
- **Audio Thread**: OpenSL ES audio callbacks

## Performance Targets

- 60 FPS on mid-range devices (Snapdragon 660+)
- < 200 MB RAM usage
- < 2 second scene transition time
- < 100 MB APK size (excluding assets)

## Build Pipeline

1. CMake compiles C++ engine to `.so` libraries
2. Gradle packages native libs into APK
3. Assets bundled into `assets/` folder
4. ProGuard optimizes Java/Kotlin code

## Future Enhancements

- Lua scripting for easier story writing
- Animation system for character sprites
- Particle effects for magic/skills
- Online features (leaderboards, cloud saves)
- Cross-platform support (iOS, Windows)