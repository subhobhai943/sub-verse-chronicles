cmake_minimum_required(VERSION 3.18.0)
project("subverse-engine")

add_library(subverse-engine SHARED
    src/jni_entry.cpp
    src/engine.cpp
    src/renderer_gles3.cpp
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
