cmake_minimum_required(VERSION 3.18.0)
project("subverse-engine")

add_library(subverse-engine SHARED
    src/main.cpp
)

find_library(log-lib log)
find_library(android-lib android)
find_library(gles3-lib GLESv3)

target_link_libraries(subverse-engine
    ${log-lib}
    ${android-lib}
    ${gles3-lib}
)