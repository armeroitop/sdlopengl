#include "input.hpp"

namespace input {
Input::Input() {
}
Input::~Input() {
}
void Input::reset() {
    mouseDelta.x = 0.0f;
    mouseDelta.y = 0.0f;
    wheelDelta = 0.0f;
}
} // namespace input

