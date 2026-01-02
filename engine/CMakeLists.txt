cmake_minimum_required(VERSION 3.22.1)

project(subverse-engine)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(subverse-engine SHARED
    src/jni_entry.cpp
    src/engine.cpp
    src/renderer_gles3.cpp
    src/asset_manager.cpp
    src/sprite_renderer.cpp
    src/dialogue_system.cpp
    src/story_manager.cpp
    src/input_manager.cpp
    src/texture.cpp
    src/image_loader.cpp
)

target_include_directories(subverse-engine PRIVATE
    include
    ${ANDROID_NDK}/sources/android/native_app_glue
)

target_link_libraries(subverse-engine
    android
    log
    GLESv3
    EGL
)
