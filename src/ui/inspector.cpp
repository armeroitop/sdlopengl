#include "inspector.hpp"

#include <imgui.h>

namespace ui {
Inspector::Inspector(editor::EditorContext& context, Scene& scene)
    : mContext(context),
    mScene(scene) {
}

Inspector::~Inspector() {
}

void Inspector::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));

    ImGui::Begin("Inspector");
    uint32_t objectId = mContext.getSelectedObjectId();
    Object* object = mScene.findObject(objectId);

    if (object == nullptr) {
        ImGui::Text("No object selected");
    } else {
        ImGui::Text("%s", object->getName().c_str());

        ImGui::Separator();

        Transform& transform = object->getTransform();

        ImGui::DragFloat3(
            "Position",
            glm::value_ptr(transform.position),
            0.1f
        );

        glm::vec3 rotationEuler = transform.getRotationEuler();
        if (ImGui::DragFloat3(
            "Rotation",
            glm::value_ptr(rotationEuler),
            1.0f
        )) {
            transform.setRotationEuler(rotationEuler);
        }


        ImGui::DragFloat3(
            "Scale",
            glm::value_ptr(transform.scale),
            0.05f
        );

    }

    ImGui::End();
    
    ImGui::PopStyleVar();

}
} // namespace ui
