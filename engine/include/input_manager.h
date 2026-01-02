#pragma once

namespace subverse {

class InputManager {
public:
    void onTouchDown(float x, float y);
    void onTouchUp(float x, float y);
    
    bool wasTapped() const { return tapped_; }
    void clearTap() { tapped_ = false; }
    
    float getTapX() const { return tapX_; }
    float getTapY() const { return tapY_; }
    
private:
    bool tapped_ = false;
    float tapX_ = 0;
    float tapY_ = 0;
};

} // namespace subverse
