#include <jni.h>
#include <string>

#include "engine.h"
#include "logger.h"

extern "C" {

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_init(JNIEnv* /*env*/, jobject /*thiz*/) {
    LOGI("JNI init()");
    subverse::GetEngine().init();
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getVersion(JNIEnv* env, jobject /*thiz*/) {
    std::string version = "SUB-verse Engine v0.2.0 (CI-ready)";
    return env->NewStringUTF(version.c_str());
}

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_onSurfaceCreated(JNIEnv* /*env*/, jobject /*thiz*/) {
    subverse::GetEngine().onSurfaceCreated();
}

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_onSurfaceChanged(JNIEnv* /*env*/, jobject /*thiz*/, jint width, jint height) {
    subverse::GetEngine().onSurfaceChanged((int)width, (int)height);
}

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_onDrawFrame(JNIEnv* /*env*/, jobject /*thiz*/) {
    subverse::GetEngine().onDrawFrame();
}

} // extern "C"
