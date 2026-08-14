#pragma once

#include <glm/glm.hpp>

enum class MouseButton
{
    Left,
    Middle,
    Right
};

namespace input {
class Input {
private:
    /* data */
public:
    bool keyW = false;
    bool keyA = false;
    bool keyS = false;
    bool keyD = false;

    bool keyShift = false;
    bool keyCtrl = false;
    bool keyAlt = false;

    bool leftMouse = false;
    bool leftMouseDown = false;
    bool leftMouseUp = false;
    
    bool middleMouse = false;
    bool middleMouseDown = false;
    bool middleMouseUp = false;
    
    bool rightMouse = false;
    bool rightMouseDown = false;
    bool rightMouseUp = false;

    glm::vec2 mouseDelta{0.0f, 0.0f};
    glm::ivec2 mouseAbsolutePosition{0.0f, 0.0f};

    float wheelDelta = 0.0f;

    Input(/* args */);
    ~Input();

    void reset();


};



} // namespace input
