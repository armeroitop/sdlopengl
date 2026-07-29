#include "viewport.hpp"

#include <imgui.h>

namespace ui {
Viewport::Viewport(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Viewport::~Viewport() {
}

void Viewport::draw() {
    ImGui::Begin("Viewport");
    ImVec2 size = ImGui::GetContentRegionAvail();

    ImGui::Text("Viewport");
    ImGui::Separator();

    ImGui::Text("Size: %.0f x %.0f", size.x, size.y);
    ImGui::End();
}

} // namespace ui
