# SUB-verse Chronicles

**SUB Project Unit — Android Isekai Visual Novel Game with Custom C++ Engine**

## Overview
SUB-verse Chronicles is an isekai-themed visual novel game for Android, built from the ground up with a custom C++ game engine. The project combines narrative storytelling with RPG mechanics in the popular isekai genre.

## Project Structure
```
sub-verse-chronicles/
├── engine/           # C++ core engine (NDK)
│   ├── src/         # Engine source code
│   ├── include/     # Engine headers
│   └── CMakeLists.txt
├── android/         # Android wrapper (Kotlin/Java)
│   ├── app/
│   └── build.gradle
├── game/            # Game content
│   ├── scripts/     # Story scripts
│   ├── data/        # Game data (characters, stats)
│   └── scenes/      # Scene definitions
├── assets/          # Game assets
│   ├── sprites/     # Character sprites
│   ├── backgrounds/ # Background images
│   ├── audio/       # Music and sound effects
│   └── ui/          # UI elements
└── docs/            # Documentation
```

## Technology Stack
- **Core Engine**: C++ (C++17)
- **Graphics API**: OpenGL ES 3.0
- **Build System**: CMake + Gradle
- **Android**: NDK r25+, Kotlin for launcher
- **Target API**: Android 8.0+ (API 26+)

## Features (Planned)
- Custom visual novel engine optimized for Android
- Branching narrative system with decision tracking
- Isekai-specific RPG mechanics (stats, skills, inventory)
- Character sprite system with expressions
- Save/load functionality
- Touch-optimized UI
- Adaptive screen resolution support

## Getting Started

### Prerequisites
- Android Studio Arctic Fox or newer
- Android NDK r25+
- CMake 3.18+
- JDK 11+

### Building
```bash
# Clone the repository
git clone https://github.com/subhobhai943/sub-verse-chronicles.git
cd sub-verse-chronicles

# Open in Android Studio and sync project
# Build will automatically compile C++ engine via CMake
```

## Development Roadmap

### Phase 1: Engine Foundation (Current)
- [x] Repository setup
- [ ] C++ engine core architecture
- [ ] Rendering pipeline (OpenGL ES)
- [ ] Asset loading system
- [ ] Input handling (touch)

### Phase 2: Visual Novel Systems
- [ ] Dialogue system
- [ ] Character sprite manager
- [ ] Background renderer
- [ ] Text rendering engine
- [ ] Decision/choice system

### Phase 3: Isekai Mechanics
- [ ] Stats and character system
- [ ] Inventory management
- [ ] Quest tracking
- [ ] Skill/ability system

### Phase 4: Android Integration
- [ ] JNI bridge
- [ ] Save/load with Android storage
- [ ] Audio system (OpenSL ES)
- [ ] Performance optimization

### Phase 5: Content & Polish
- [ ] Story scripting
- [ ] Art asset integration
- [ ] UI/UX refinement
- [ ] Testing & debugging

## Contributing
This is a SUB project unit development. Contributions welcome!

## License
TBD

## Contact
Subhobhai - [@subhobhai943](https://github.com/subhobhai943)

Project Link: [https://github.com/subhobhai943/sub-verse-chronicles](https://github.com/subhobhai943/sub-verse-chronicles)