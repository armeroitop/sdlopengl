#pragma once
#include "camera/camera.hpp"
#include "input/input.hpp"

namespace camera {
class CameraController {
private:
    void updateMovement(
        Camera& camera,
        const input::Input& input,
        float deltaTime
    ) const;

    void updateRotation(
        Camera& camera,
        const input::Input& input
    ) const;

   void updateOrbit(Camera& camera, const input::Input& input) const;
   void updatePan(Camera& camera, const input::Input& input) const;
   void updateZoom(Camera& camera, const input::Input& input) const;
public:
    CameraController(/* args */);

    void update(
        Camera& camera,
        const input::Input& input,
        float deltaTime
    ) const;
};



} // namespace camera

