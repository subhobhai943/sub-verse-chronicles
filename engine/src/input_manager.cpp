#include "input_manager.h"
#include "logger.h"

namespace subverse {

void InputManager::onTouchDown(float x, float y) {
    tapX_ = x;
    tapY_ = y;
}

void InputManager::onTouchUp(float x, float y) {
    tapped_ = true;
    LOGI("Tap at (%.1f, %.1f)", x, y);
}

} // namespace subverse
