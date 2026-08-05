#include "camera_controller.hpp"

namespace camera {
void CameraController::updateMovement(Camera& camera, const input::Input& input, float deltaTime) const {

    if (input.keyW) {
        camera.moveForward(deltaTime);
    }
    if (input.keyS) {
        camera.moveBackward(deltaTime);
    }
    if (input.keyA) {
        camera.moveLeft(deltaTime);
    }
    if (input.keyD) {
        camera.moveRight(deltaTime);
    }
}

void CameraController::updateRotation(Camera& camera, const input::Input& input) const {

    if (input.rightMouse) {
        camera.mouseLook(input.mouseDelta.x, input.mouseDelta.y);
    }
}


void CameraController::updateOrbit(Camera& camera, const input::Input& input) const {
     if (input.keyAlt) {
        camera.orbit(input.mouseDelta.x, input.mouseDelta.y);
    }
}

void CameraController::updatePan(Camera& camera, const input::Input& input) const {
    if (input.middleMouse){
        camera.pan(input.mouseDelta.x, input.mouseDelta.y);
    }
}

void CameraController::updateZoom(Camera& camera, const input::Input& input) const {

    if (input.wheelDelta != 0.0f) {
        camera.zoom(input.wheelDelta);
    }

}

CameraController::CameraController() {

}

void CameraController::update(
    Camera& camera,
    const input::Input& input,
    float deltaTime) const {

    updateMovement(camera, input, deltaTime);

    updateRotation(camera, input);

    updateZoom(camera, input);

    updatePan(camera, input);

    updateOrbit(camera, input);
}

}// namespace camera