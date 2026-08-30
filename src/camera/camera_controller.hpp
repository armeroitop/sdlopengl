#pragma once
#include "editor/editor_context.hpp"
#include "scene/scene.hpp"
#include "camera/camera.hpp"
#include "input/input.hpp"
#include <optional>


namespace camera {
class CameraController {
private:
    editor::EditorContext& mContext;
    Scene& mScene;

    void updateMovement(Camera& camera, const input::Input& input, float deltaTime) const;
    void updateRotation(Camera& camera, const input::Input& input) const;
    void updateOrbit(Camera& camera, const input::Input& input) const;
    void updatePan(Camera& camera, const input::Input& input) const;
    void updateZoom(Camera& camera, const input::Input& input, const std::optional<glm::vec3>& zoomPoint) const;
    void handleFocus(Camera& camera, const input::Input& input) const;

public:
    CameraController(editor::EditorContext& context, Scene& scene);

    void update(Camera& camera, const input::Input& input, float deltaTime, const std::optional<glm::vec3>& zoomPoint) const;
};



} // namespace camera

