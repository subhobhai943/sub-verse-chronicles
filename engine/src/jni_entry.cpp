#include <jni.h>
#include <string>
#include <android/asset_manager_jni.h>

#include "engine.h"
#include "logger.h"

extern "C" {

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_init(JNIEnv* env, jobject /*thiz*/, jobject assetManager) {
    AAssetManager* mgr = AAssetManager_fromJava(env, assetManager);
    subverse::GetEngine().init(mgr);
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getVersion(JNIEnv* env, jobject /*thiz*/) {
    std::string version = "SUB-verse Engine v1.1.0 (Production VN)";
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
Java_in_sub_unit_subverse_NativeEngine_advance(JNIEnv* /*env*/, jobject /*thiz*/) {
    subverse::GetEngine().advance();
}

JNIEXPORT void JNICALL
Java_in_sub_unit_subverse_NativeEngine_choose(JNIEnv* /*env*/, jobject /*thiz*/, jint idx) {
    subverse::GetEngine().choose((int)idx);
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getSpeaker(JNIEnv* env, jobject /*thiz*/) {
    auto s = subverse::GetEngine().getSpeaker();
    return env->NewStringUTF(s.c_str());
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getText(JNIEnv* env, jobject /*thiz*/) {
    auto s = subverse::GetEngine().getText();
    return env->NewStringUTF(s.c_str());
}

JNIEXPORT jint JNICALL
Java_in_sub_unit_subverse_NativeEngine_getChoiceCount(JNIEnv* /*env*/, jobject /*thiz*/) {
    return (jint)subverse::GetEngine().getChoiceCount();
}

JNIEXPORT jstring JNICALL
Java_in_sub_unit_subverse_NativeEngine_getChoiceText(JNIEnv* env, jobject /*thiz*/, jint idx) {
    auto s = subverse::GetEngine().getChoiceText((int)idx);
    return env->NewStringUTF(s.c_str());
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
