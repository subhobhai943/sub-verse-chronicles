cmake_minimum_required(VERSION 3.18.0)
project("subverse-engine")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(subverse-engine SHARED
    src/jni_entry.cpp
    src/engine.cpp
    src/renderer_gles3.cpp
    src/asset_manager.cpp
    src/texture.cpp
    src/sprite_renderer.cpp
    src/dialogue_system.cpp
    src/story_manager.cpp
    src/input_manager.cpp
)

target_include_directories(subverse-engine PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/include
)

find_library(log-lib log)
find_library(android-lib android)
find_library(gles3-lib GLESv3)

target_link_libraries(subverse-engine
    ${log-lib}
    ${android-lib}
    ${gles3-lib}
)
