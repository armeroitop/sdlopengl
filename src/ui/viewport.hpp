#pragma once
#include <glad/glad.h>
#include <imgui.h>
#include <ImGuizmo.h>
#include <optional>

#include "editor/editor_context.hpp"
#include "scene/scene.hpp"
#include "render/framebuffer.hpp"
#include "camera/camera.hpp"
#include "input/input.hpp"
#include "math/ray.hpp"



namespace ui {
class Viewport {

private:
    editor::EditorContext& mContext;
    Scene& mScene;
    Camera& mCamera;

    render::Framebuffer mFramebuffer;

    ImVec2 mSize;
    ImVec2 mImagePos;

    glm::vec2 screenToNDC(const glm::vec2& mouseAbsolutePosition) const;

    std::optional<glm::vec3> rayPlaneIntersection(
        const math::Ray& ray,
        const glm::vec3& planePoint,
        const glm::vec3& planeNormal
    ) const;

public:
    Viewport(editor::EditorContext& context, Scene& scene, Camera& camera);
    ~Viewport();

    void draw();
    void update(const input::Input& input);

    void begin();
    void beginRender();
    void endRender();

    void end();

    float getAspectRatio() const;
    int getWidth() const;
    int getHeight() const;

    bool isMouseOver(const glm::ivec2& mouseAbsolutePosition) const;

    math::Ray screenToRay(const glm::vec2& mouseAbsolutePosition) const;
    math::Ray worldToLocalRay(const math::Ray& worldRay, const glm::mat4& modelMatrix) const;

    std::optional<glm::vec3> getZoomPoint(const input::Input& input) const;

};

} // namespace ui