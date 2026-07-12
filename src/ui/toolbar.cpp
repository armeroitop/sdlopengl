#include "toolbar.hpp"

#include <imgui.h>

namespace ui {

Toolbar::Toolbar(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Toolbar::~Toolbar() {
}

void Toolbar::draw() {
    ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(
        ImVec2(60, ImGui::GetIO().DisplaySize.y),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar;

    ImGui::Begin("Toolbar", nullptr, flags);

    ImGui::Button("S", ImVec2(40, 40));
    ImGui::Button("M", ImVec2(40, 40));
    ImGui::Button("R", ImVec2(40, 40));
    ImGui::Button("E", ImVec2(40, 40));

    ImGui::Separator();

    ImGui::Button("+", ImVec2(40, 40));

    if (ImGui::Button("Cube", ImVec2(40, 40))) {
        Transform t;
        t.position = glm::vec3(0.0f, 0.0f, -2.0f);
        mScene.createCubeMesh(t);
    }

    ImGui::End();
}

} // namespace ui


