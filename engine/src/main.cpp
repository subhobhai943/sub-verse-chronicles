#include <jni.h>
#include <string>
#include "../include/logger.h"

extern "C" {

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_init(JNIEnv* env, jobject /* this */) {
    LOGI("SUB-verse Engine Initializing...");
    // Future: Initialize audio, renderer, and asset manager here
    LOGI("SUB-verse Engine Initialized successfully.");
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getVersion(JNIEnv* env, jobject /* this */) {
    std::string version = "SUB-verse Engine v0.1.0 (Alpha)";
    return env->NewStringUTF(version.c_str());
}

}