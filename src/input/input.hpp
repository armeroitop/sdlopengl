#pragma once

#include <glm/glm.hpp>

enum class MouseButton {
    Left,
    Middle,
    Right
};

namespace input {
class Input {
private:
    /* data */
public:

    // Estado
    bool keyW = false;
    bool keyA = false;
    bool keyS = false;
    bool keyD = false;

    bool keyF = false;
    
    bool keyShift = false;
    bool keyCtrl = false;
    bool keyAlt = false;
    
    bool leftMouse = false;
    bool middleMouse = false;
    bool rightMouse = false;
    
    // Transición
    bool keyFDown = false;
    bool keyFUp = false;

    bool leftMouseDown = false;
    bool leftMouseUp = false;

    bool middleMouseDown = false;
    bool middleMouseUp = false;

    bool rightMouseDown = false;
    bool rightMouseUp = false;

    // Movimiento
    glm::vec2 mouseDelta{ 0.0f, 0.0f };
    glm::ivec2 mouseAbsolutePosition{ 0.0f, 0.0f };

    float wheelDelta = 0.0f;

    // Eventos de la aplicación
    bool quitRequested = false;

    Input(/* args */);
    ~Input();

    void reset();

    // Actualiza el input del frame
    void update();


};



} // namespace input
