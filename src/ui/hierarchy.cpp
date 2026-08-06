#include "hierarchy.hpp"

#include <imgui.h>

namespace ui {
Hierarchy::Hierarchy(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Hierarchy::~Hierarchy() {
}

void Hierarchy::draw() {
    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(10, 10));
    ImGui::Begin("Hierarchy");

    for (const auto& obj : mScene.getObjects()) {
        bool selected = obj.getId() == mContext.getSelectedObjectId();

        if (ImGui::Selectable(obj.getName().c_str(), selected)) {
            mContext.setSelectedObjectId(obj.getId());
        }

    }
    ImGui::PopStyleVar();
    ImGui::End();
}

} // namespace ui
