#include "camera_controller.hpp"


#include <iostream>

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
    if (input.middleMouse) {
        camera.pan(input.mouseDelta.x, input.mouseDelta.y);
    }
}

void CameraController::updateZoom(Camera& camera, const input::Input& input, const std::optional<glm::vec3>& zoomPoint) const {

    if (input.wheelDelta != 0.0f) {

        if (zoomPoint) {
            camera.zoomAtPoint(input.wheelDelta, *zoomPoint);
        } else {
            //camera.zoom(input.wheelDelta); // Lo apago para que no se haga zoom fuera del viewport
        }
    }
}

void CameraController::handleFocus(Camera& camera, const input::Input& input) const {
    if (input.keyFDown) {
        u_int32_t mCurrentSelectedObjectId = mContext.getSelectedObjectId();

        if (Object* object = mScene.findObject(mCurrentSelectedObjectId)) {
            camera.focus(
                object->getTransform().position,
                object->getWorldBoundingRadius()
            );
        }
    }
}

CameraController::CameraController(editor::EditorContext& context, Scene& scene)
    : mContext(context), mScene(scene) {
}

void CameraController::update(
    Camera& camera,
    const input::Input& input,
    float deltaTime,
    const std::optional<glm::vec3>& zoomPoint) const {

    updateMovement(camera, input, deltaTime);

    updateRotation(camera, input);

    updateZoom(camera, input, zoomPoint);

    updatePan(camera, input);

    updateOrbit(camera, input);

    handleFocus(camera, input);
}

}// namespace camera