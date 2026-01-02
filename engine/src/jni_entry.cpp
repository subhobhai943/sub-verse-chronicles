#include <jni.h>
#include <string>
#include <android/asset_manager_jni.h>

#include "engine.h"
#include "logger.h"

extern "C" {

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_init(JNIEnv* env, jobject thiz, jobject assetManager) {
    LOGI("JNI init()");
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    subverse::GetEngine().init(mgr);
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getVersion(JNIEnv* env, jobject /*thiz*/) {
    std::string version = "SUB-verse Engine v1.0.0 (Complete VN)";
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

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_onTouchDown(JNIEnv* /*env*/, jobject /*thiz*/, jfloat x, jfloat y) {
    subverse::GetEngine().onTouchDown(x, y);
}

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_onTouchUp(JNIEnv* /*env*/, jobject /*thiz*/, jfloat x, jfloat y) {
    subverse::GetEngine().onTouchUp(x, y);
}

} // extern "C"
