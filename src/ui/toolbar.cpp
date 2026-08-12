#include "toolbar.hpp"



namespace ui {
void Toolbar::addButton(const char* label, editor::Tool tool) {

    bool selected = (mContext.getTool() == tool);

    ImGui::PushStyleColor(ImGuiCol_Button, getButtonColor(selected));

    if (ImGui::Button(label)) {
        mContext.setTool(tool);
    }

    ImGui::PopStyleColor(); // Restaura el estilo
}

void Toolbar::addTransformModeButton(const char* label, editor::TransformMode mode) {

    bool selected = (mContext.getTransformMode() == mode);

    ImGui::PushStyleColor(ImGuiCol_Button, getButtonColor(selected));

    if (ImGui::Button(label)) {
        mContext.setTransformMode(mode);
    }

    ImGui::PopStyleColor();
}

ImVec4 Toolbar::getButtonColor(bool selected) const {

    if (selected) {
        return ImVec4(1.0f, 0.0f, 0.0f, 1.0f);
    }
    return ImVec4(0.26f, 0.59f, 0.98f, 0.40f);
}


Toolbar::Toolbar(editor::EditorContext& context, Scene& scene)
    :mContext(context), mScene(scene) {
}

Toolbar::~Toolbar() {
}

void Toolbar::draw() {

    ImGui::Begin("Toolbar");

    addButton("Sel", editor::Tool::Select);
    ImGui::SameLine();

    // Herramientas de movimiento
    addButton("M", editor::Tool::Move);
    ImGui::SameLine();
    addButton("R", editor::Tool::Rotate);
    ImGui::SameLine();
    addButton("S", editor::Tool::Scale);
    ImGui::SameLine();

    ImGui::Text(" | ");
    ImGui::SameLine();
    

    // Modo de transformación
    addTransformModeButton("L", editor::TransformMode::Local);
    ImGui::SameLine();
    addTransformModeButton("W", editor::TransformMode::World);
    ImGui::SameLine();
    
    ImGui::Text(" | ");
    ImGui::SameLine();

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


