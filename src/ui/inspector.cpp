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
        
        ImGui::DragFloat3(
            "Rotation",
            glm::value_ptr(transform.rotation),
            1.0f
        );

        ImGui::DragFloat3(
            "Scale",
            glm::value_ptr(transform.scale),
            0.05f
        );

    }


    ImGui::End();

}
} // namespace ui
