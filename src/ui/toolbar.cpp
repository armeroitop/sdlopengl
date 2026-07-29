#include "toolbar.hpp"

#include <imgui.h>

namespace ui {

Toolbar::Toolbar(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Toolbar::~Toolbar() {
}

void Toolbar::draw() {
    /* ImGui::SetNextWindowPos(ImVec2(0, 0), ImGuiCond_Always);
    ImGui::SetNextWindowSize(
        ImVec2(60, ImGui::GetIO().DisplaySize.y),
        ImGuiCond_Always
    );

    ImGuiWindowFlags flags =
        ImGuiWindowFlags_NoMove |
        ImGuiWindowFlags_NoResize |
        ImGuiWindowFlags_NoCollapse |
        ImGuiWindowFlags_NoTitleBar; 

    ImGui::Begin("Toolbar", nullptr, flags);*/

    ImGui::Begin("Toolbar");


    ImGui::Button("S"); ImGui::SameLine();
    ImGui::Button("M"); ImGui::SameLine();
    ImGui::Button("R"); ImGui::SameLine();
    ImGui::Button("E"); ImGui::SameLine();

    ImGui::Button("+"); ImGui::SameLine();

    if (ImGui::Button("Cube")) {
        Transform t;
        t.position = glm::vec3(0.0f, 0.0f, -2.0f);
        mScene.createCubeMesh(t);
    }

    ImGui::End();
}

} // namespace ui


